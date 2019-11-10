
#include "scene_list_view.h"
#include "../common/primitive_factory.h"
#include "scene_presenter.h"

SceneListView::SceneListView() { presenter_ = new ScenePresenter(this); }

void SceneListView::userInput() {
  do {
    //вводим с клавиатуры тип примитива для создания
    std::cout << "Введите тип примитива для создания (rect или circle)"
              << std::endl;
    std::string shapeType;
    std::cin >> shapeType;
    //создаем примитив
    PrimitivePtr pr = createPrimitive(shapeType, {10, 10});
    //говорим презентору что создался новый притмитив
    presenter_->onNewPrimitive(pr);

  } while (true);
}
