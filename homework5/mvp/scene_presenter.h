#ifndef SCENE_PRESENTER_H
#define SCENE_PRESENTER_H

#include "i_scene_view.h"
#include "scene_model.h"
/**
 * @brief Отвечает за получение данных пользовательского ввода
 * получает событие от view и обрабатывает логику результата этого события
 * в случае добавления нового примитива - записывает этот примитив в модель и
 * вызывает у вью перерисовку всех примитивов находящихся в модели
 */
class ScenePresenter {
 public:
  ScenePresenter(ISceneView *view) : view_(view) {}
  //
  void onNewPrimitive(PrimitivePtr pr) {
    model_.addPrimitive(pr);
    for (int i = 0; i < model_.primitivesSize(); i++) {
      PrimitivePtr primitive = model_.primitiveAt(i);
      view_->drawPrimitive(primitive);
    }
    // view_->updatePrimitivesCountLabel(model_.primitivesSize());
  }

 private:
  SceneModel model_;
  ISceneView *view_;
};

#endif  // SCENE_PRESENTER_H
