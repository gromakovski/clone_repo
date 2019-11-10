#ifndef SCENE_LIST_VIEW_H
#define SCENE_LIST_VIEW_H

#include "../common/primitive.h"
#include "i_scene_view.h"
#include "iostream"

class ScenePresenter;

/**
 * @brief Активити или виджет для отображения графических примитивов
 */
class SceneListView : public ISceneView {
 public:
  SceneListView();
  void userInput() override;
  //нарисовать примитив
  void drawPrimitive(PrimitivePtr pr) override {
    std::cout << "draw on list - " << pr->name() << pr->pos().x_ << pr->pos().y_
              << std::endl;
  }
  //обновляет количество примитивов на представлении

 private:
  ScenePresenter *presenter_;
};

#endif  // SCENE_LIST_VIEW_H
