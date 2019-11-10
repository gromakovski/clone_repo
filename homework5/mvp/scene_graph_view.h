#ifndef SCENE_VIEW_H
#define SCENE_VIEW_H

#include "../common/primitive.h"
#include "i_scene_view.h"
#include "iostream"

class ScenePresenter;

/**
 * @brief Активити или виджет для отображения графических примитивов
 */
class SceneGraphView : public ISceneView {
 public:
  SceneGraphView();
  void userInput() override;
  //нарисовать примитив
  void drawPrimitive(PrimitivePtr pr) override { pr->draw(); }
  //обновляет количество примитивов на представлении
  void updatePrimitivesCountLabel(int count) {
    std::cout << "primitives count is " << count << std::endl;
  }

 private:
  ScenePresenter *presenter_;
};

#endif  // SCENE_VIEW_H
