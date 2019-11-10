#ifndef PRIMITIVE_SAVER_H
#define PRIMITIVE_SAVER_H

/** @addtogroup grapheditor
 *
 * @{
 */

#include <iostream>
#include "../mvc/scene_model.h"
#include "primitive.h"
#include "primitive_visitor.h"
/**
 * @brief Класс для сохранения в разные
 */
class PrimitiveSaver {
 public:
  PrimitiveSaver() {}
  void setModel(SceneModelPtr model) { model_ = model; }
  void setSaveStrategy(IPrimitiveVisitor *visitor) { visitor_ = visitor; }
  void save() {
    if (visitor_) {
      for (int i = 0; i < model_->primitivesSize(); i++) {
        model_->primitiveAt(i)->accept(*visitor_);
      }
      std::cout << "document saved";
    }
  }

 private:
  IPrimitiveVisitor *visitor_ = nullptr;
  SceneModelPtr model_;
};

/** @} */  // end of grapheditor

#endif  // PRIMITIVE_SAVER_H
