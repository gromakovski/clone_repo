#ifndef I_SCENE_VIEW_H
#define I_SCENE_VIEW_H

#include "../common/primitive.h"

/**
 * @brief Интерфейс для представлений
 * Поддерживает обработку пользовательского ввода
 * и отрисовку примитива
 */
class ISceneView {
 public:
  //нарисовать примитив
  virtual void drawPrimitive(PrimitivePtr pr) = 0;
  //обработка пользовательского ввода
  virtual void userInput() = 0;
};

#endif  // I_SCENE_VIEW_H
