#ifndef SCENE_PRESENTER_H
#define SCENE_PRESENTER_H

/** @addtogroup grapheditor
 *
 * @{
 */

#include "../common/primitive_factory.h"
#include "scene_model.h"
#include "scene_view.h"

/**
 * @brief Класс предоставляет интерфейс для взаимодействия пользователя и
 * модели. Позволяет добавлять  и удалять примитивы в модель. При
 * добавлении/удалении уведомляет view о том что ей надо перерисоваться
 */
class SceneController {
 public:
  SceneController(SceneView &view) : view_(&view) {}
  void setModel(SceneModelPtr model) { model_ = model; }
  void onNewPrimitive(std::string shapeType) {
    PrimitivePtr pr = createPrimitive(shapeType, {10, 10});
    model_->addPrimitive(pr);
    view_->drawPrimitives();
  }
  void onRemovePrimitive(int i) {
    model_->removePrimitive(i);
    view_->drawPrimitives();
  }

 private:
  SceneModelPtr model_;
  SceneView *view_;
};

/** @} */  // end of grapheditor

#endif  // SCENE_PRESENTER_H
