#ifndef SCENE_MODEL_H
#define SCENE_MODEL_H

#include <vector>
#include "../common/primitive.h"
#include "memory"

/** @addtogroup grapheditor
 *
 * @{
 */

/**
 * @brief Класс хранит в себе список примитивов и реализует
 * функци для работы с этим списком. Сохранение модели
 * могло бы быть реализовано в ней же, но для большей гибкости
 * вынесено в класс PrimitiveSaver
 */
class SceneModel {
 public:
  SceneModel() {}
  void addPrimitive(PrimitivePtr pr) { primitives_.push_back(pr); }
  void removePrimitive(int i) { primitives_.erase(primitives_.begin() + i); }
  int primitivesSize() { return primitives_.size(); }
  PrimitivePtr primitiveAt(int i) {
    if (i < primitives_.size())
      return primitives_[i];
    else
      throw std::out_of_range(" ");
  }

  void load(std::string fileName) {
    std::cout << "load from file " + fileName;
    /*псевдокод
     * clearModel
        for (auto primitive : fileContent) {
          PrimitivePtr pr = createPrimitive(primitive.primitiveType);
          addPrimitive()
        }
        */
  }

 private:
  std::vector<PrimitivePtr> primitives_;
};
using SceneModelPtr = std::shared_ptr<SceneModel>;

/** @} */  // end of grapheditor

#endif  // SCENE_MODEL_H
