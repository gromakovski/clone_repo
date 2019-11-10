#ifndef PRIMITIVE_FACTORY_H
#define PRIMITIVE_FACTORY_H

#include <iostream>
#include <map>
#include <memory>
#include "primitive.h"

/** @addtogroup grapheditor
 *
 * @{
 */

/**
 * @brief Абстрактная фабрика. Обьявляет фабричный метод
 * создания примитивов
 */
class IPrimitiveFactory {
 public:
  virtual PrimitivePtr createPrimitive(Position &pos) = 0;
};
/**
 * @brief Фабрика прямоугольников
 */
class RectFactory : public IPrimitiveFactory {
 public:
  PrimitivePtr createPrimitive(Position &pos) override {
    return std::make_shared<Rect, Position &, int, int>(pos, 10, 10);
  }
};
/**
 * @brief Фабрика окружностей
 */
class CircleFactory : public IPrimitiveFactory {
 public:
  PrimitivePtr createPrimitive(Position &pos) override {
    return std::make_shared<Circle, Position &, int>(pos, 10);
  }
};
//создание конкретных фабрик
static std::map<std::string, IPrimitiveFactory *> createPrimitiveFactories() {
  std::map<std::string, IPrimitiveFactory *> primitiveFactories;
  primitiveFactories["rect"] = new RectFactory();
  primitiveFactories["circle"] = new CircleFactory();
  return primitiveFactories;
}

static std::map<std::string, IPrimitiveFactory *> primitiveFactories =
    createPrimitiveFactories();

//метод для создания конкретного примитива, type - тип создаваемого примитива.
static PrimitivePtr createPrimitive(std::string type, Position &&pos) {
  return primitiveFactories[type]->createPrimitive(pos);
}

/** @} */  // end of grapheditor

#endif  // PRIMITIVE_FACTORY_H
