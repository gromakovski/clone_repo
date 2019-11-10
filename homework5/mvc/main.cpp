#include <iostream>
#include <memory>
#include <vector>

#include "../common/primitive_saver.h"
#include "scene_controller.h"
#include "scene_model.h"
#include "scene_view.h"

// http://yarik-raider.blogspot.com/2010/01/mvc.html

const std::string CMD_ADD_PRIMITIVE = "ap";
const std::string CMD_REMOVE_PRIMITIVE = "rp";
const std::string CMD_NEW_DOCUMENT = "newdoc";
const std::string CMD_SAVE_DOCUMENT = "savedoc";
const std::string CMD_LOAD_DOCUMENT = "loaddoc";

const std::string PRIMITIVE_RECT = "rect";
const std::string PRIMITIVE_CIRCLE = "circle";

void userInput(SceneController &controller,
               SceneView &sceneView /*, DocumentReadWriteController*/) {
  SceneModelPtr model;
  do {
    std::cout << "Введите команду - " + CMD_ADD_PRIMITIVE + " " +
                     CMD_REMOVE_PRIMITIVE + " " + CMD_NEW_DOCUMENT + " " +
                     CMD_SAVE_DOCUMENT + " " + CMD_LOAD_DOCUMENT
              << std::endl;
    std::string command;
    std::cin >> command;
    if (command == CMD_ADD_PRIMITIVE) {
      std::string shapeType;
      std::cin >> shapeType;
      controller.onNewPrimitive(shapeType);
    }
    if (command == CMD_REMOVE_PRIMITIVE) {
      int index;
      std::cin >> index;
      controller.onRemovePrimitive(index);
    }
    if (command == CMD_NEW_DOCUMENT) {
      model = std::make_shared<SceneModel>();
      sceneView.setModel(model);
      controller.setModel(model);
      std::cout << "new document created";
    }
    if (command == CMD_SAVE_DOCUMENT) {
      std::string fileName;
      std::cin >> fileName;
      //создаем экземпляр сохранятеля устанавливаем
      //модель , стратегию и сохраняем
      DocumentSaveToFilePrimitiveVisitor visitor("primitives.txt");
      // DocumentSendToPrinterPrimitiveVisitor visitor(printerHandler);
      PrimitiveSaver saver;
      saver.setModel(model);
      saver.setSaveStrategy(&visitor);
      saver.setSaveStrategy(&visitor);
      saver.save();
    }
    if (command == CMD_LOAD_DOCUMENT) {
      std::string fileName;
      std::cin >> fileName;
      model->load(fileName);
      std::cout << "document loaded";
    }

  } while (true);
}

int main(int argc, char const *argv[]) {
  SceneView sceneView;
  SceneController controller{sceneView};

  userInput(controller, sceneView);

  return 0;
}

//Используемые паттерны и мотивация их использования
// 1. FACTORY METHOD (или это все таки ABSTRACT FACTORY?)
//Мотивация: Позволяет создавать примитивы не привязываясь к их конкретному типу
//т.е. само создание конкретных примитивов реализовано в их фабриках
//благодаря этому можно добавлять новые типы примитивов не затрагивая ядро
//программы. scene_controller.h:13 (эту строчку можно никогда не менять)
// 2. VISITOR
//Мотивация: Позволяет совершать операции над иерархию примитивов,
//не затрагивая код самих примитивов. Сейчас реализовано сохранение иерархии в
//файл - DocumentSaveToFilePrimitiveVisitor.
// 3. STRATEGY
//Мотивация: Позволяет  управлять выбором конкретного алгоритма  через прослойку
// PrimitiveSaver. Класс PrimitiveSaver управляет иерархией классов производных
// от IPrimitiveVisitor (в числе которых DocumentSaveToFilePrimitiveVisitor) и
//предоставляет интерфейс выбора алгоритма сохранения иерархии примитивов с
//помощью PrimitiveSaver::setSaveStrategy
// 4. MODEL VIEW CONTROLLER
//Мотивация:: Ну собсьтвенно говоря ModelView часть паттерна позволяет разделить
//логику модели и представления в отдельные классы  и сделать так что модель
//ничего не знает о вью (так как ей это не нужно (что логично:))). А вью
//знает о модели так как ей надо в себе отображаьб данные из модели.
//Тепер о Controller части паттерна. Контроллер нужен для того чтобы
//инкапсулировать логику внешних воздействий на модель (от пользователя
//например). В классической вкрсии паттерна контроллер после обработки действия
//пользователя изменяет модель и уведомляет вью о том что изменил модель (чтобы
//оно перерисовалось) В продвинутой версии модель  использует механизм сигналов
//(или паттерн OBSERVER) для того чтобы уведомлять вью о изменениях в себе.
//Таким образом убираеться связь между контроллером и вью
// OBSERVER
//Мотивация: развязать вью и контроллер
//Пример здесь http://yarik-raider.blogspot.com/2010/01/mvc.html
//Добавлять к себе в реализацию не стал так как боюсь переусложнить
//код и просто лень:)

/*
  Общие филосовские размышления:

1 Можно было бы в интерфейс Primitive добавить функции для сохранения и загрузки
примитива (и потом переопределять их реализацию для производных примитивов) но
это не очень хорошо смешивать разные функционалы в одной сущности Может
получиться не расширяемо если например у нас было реализовано сохранение в файл
sql бд , а понадобиться добавить сохранение в облако через (JSON) сокет...
 Поэтому решено было в интерфейсе Primitive оставить только свойства примитива
 а для реализации логики работы с иерархией Primitive производных классов
воспользоваться паттерном Visitor и создавать нужного Visitora на каждую

2 В тоже время отрисовка примитивов Primitive::draw реализована по классической
схеме базовая чисто виртуальная функция и перелоопределения в каждом конкретном
подклассе. (хотя можно было сделать опять таки какого нибудь
DrawPrimitiveVisitor).
Недостатки текущей реализации отрисовки примитивов заключаются в том что при
необходимости добавления нового способа их отрисовки (например текущая отрисовка
была сделана на opengl а захотелось добавить отрисовку на directx) придется ....
если следовать текущему стилю архитектуры создать в интерфейсе функцию
IPrimitive::draw1() и реализовать ее в каждом подклассе с помощью directx
Если же сделать отрисовку через связку Visitor и Strategy ( каждый
способ отрисовки для всей иерархии был бы конкретным подклассом посетителя
и эти посетители бы являлись стратегиями для какого то класса который ими
управляет в зависимости от настройки. То пользуясь этим классом можно бывло бы
перенастраивать на горячую стратегию отрисовки.) Ну и добавление нового способа
отрисовки сводилось бы к написанию нового подкласса визитора. НО что меня
смущает во всей этой истории с визиторами? То что вот  визитор для сохранения
иерархии в файл у меня в голове ложиться хорошо. А вот визитор для отрисовки
примитивов мне не очень нравиться так как, отрисовка каждого примитива
индивидуальна и может зависить от чего то еще например свойств  других
примитивов. Ну и весь код отрисовки для всех примитивов будет слишком большой
чтобы запихивать его в один класс визитора. Аа кажется понял что меня смущает!!
В случае с сохранением в файл визитор выполняет одну четкую задачу - сохранение
иерархии в файл. А в случае с отриосвкой... отрисовка каждого примитива как бы
своя мини задача и запихивание их в одно место противоречит принципу Separation
of concerns


3. Для загрузки документа паттерны не придумал:( Просто парсится файл
//и в зависимости от содержимого создаются те или иные примитивы и добавляются в
модель)

4. По хорошему модель вью и контроллер должны быть связаны друг с другом
через абстракции т.е. должны быть интерфейсы IModel, IView, IController
А функции setModel должны быть реализованы в этих базовых классах.
Эх ладно не буду дальше расписывать реализацию MVC фремворка библиоткеи Qt
кому это интересно...:) Если интересно то вот
https://doc.qt.io/qt-5/model-view-programming.html
 */
