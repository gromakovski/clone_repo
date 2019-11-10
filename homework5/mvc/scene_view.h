#ifndef SCENE_VIEW_H
#define SCENE_VIEW_H

/** @addtogroup grapheditor
 *
 * @{
 */

#include "scene_model.h"
/**
 * @brief Класс для отображения модели
 */
class SceneView {
 public:
  void setModel(SceneModelPtr model) { model_ = model; }
  void drawPrimitives() {
    for (int i = 0; i < model_->primitivesSize(); i++) {
      model_->primitiveAt(i)->draw();
    }
  }

 private:
  SceneModelPtr model_;
};

/** @} */  // end of grapheditor

#endif  // SCENE_VIEW_H
