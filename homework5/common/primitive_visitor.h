#ifndef PRIMITIVE_VISITOR_H
#define PRIMITIVE_VISITOR_H

/** @addtogroup grapheditor
 *
 * @{
 */

#include <iostream>
#include "primitive.h"
/**
 * @brief Базовый визитор для осуществления каких либо операций с иерархией
 * примитивов
 */
class IPrimitiveVisitor {
 public:
  virtual void visit(Rect* r) = 0;
  virtual void visit(Circle* r) = 0;
};
/**
 * @brief Визитор для сохранения иерархии примитивов в файл
 */
class DocumentSaveToFilePrimitiveVisitor : public IPrimitiveVisitor {
 public:
  DocumentSaveToFilePrimitiveVisitor(std::string fileName)
      : fileName_(fileName) {}
  void visit(Rect* r) override {
    std::cout << "save" << r->name() << r->pos().x_ << r->pos().y_ << r->width()
              << r->height();
  }
  void visit(Circle* r) override {
    std::cout << "save" << r->name() << r->pos().x_ << r->pos().y_
              << r->radius();
  }

 private:
  std::string fileName_;
};

/** @} */  // end of grapheditor

#endif  // PRIMITIVE_FACTORY_H
