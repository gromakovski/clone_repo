#ifndef SCENE_MODEL_H
#define SCENE_MODEL_H

#include <vector>
#include "../common/primitive.h"

/**
 * @brief Контейнер для графических примитивов (MODEL)
 */
class SceneModel {
 public:
  void addPrimitive(PrimitivePtr pr) { primitives_.push_back(pr); }
  void removePrimitive(int i) { primitives_.erase(primitives_.begin() + i); }
  int primitivesSize() { return primitives_.size(); }
  PrimitivePtr primitiveAt(int i) { return primitives_[i]; }

 private:
  std::vector<PrimitivePtr> primitives_;
};

#endif  // SCENE_MODEL_H
