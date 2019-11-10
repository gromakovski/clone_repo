#ifndef PRIMITIVE_H
#define PRIMITIVE_H

/** @defgroup grapheditor graph_editor */
/** @addtogroup grapheditor
 *
 * @{
 */

#include <iostream>
#include <memory>

class IPrimitiveVisitor;

struct Position {
  Position() = default;
  Position(int x, int y) : x_(x), y_(y) {}
  int x_ = 0;
  int y_ = 0;
};
/**
 * @brief Базовый класс графического примитива
 */
class IPrimitive {
 public:
  IPrimitive(Position pos) : pos_(pos) {}
  virtual void draw() = 0;
  virtual std::string name() = 0;
  Position pos() { return pos_; }
  virtual void accept(class IPrimitiveVisitor &v) = 0;

 protected:
  Position pos_;
};
using PrimitivePtr = std::shared_ptr<IPrimitive>;

/**
 * @brief Класс реализующий в себе функционал прямоугольника
 */
class Rect : public IPrimitive {
 public:
  Rect(Position pos, int width, int height)
      : IPrimitive(pos), width_(width), height_(height) {}
  void draw() override {
    std::cout << "draw rect " << pos_.x_ << width_ << height_ << std::endl;
  }
  std::string name() override { return "Rect"; }
  int width() { return width_; }
  int height() { return height_; }
  void accept(IPrimitiveVisitor &v) override;

 private:
  int width_;
  int height_;
};
/**
 * @brief Класс реализующий в себе функционал круга
 */
class Circle : public IPrimitive {
 public:
  Circle(Position pos, int radius) : IPrimitive(pos), radius_(radius) {}
  void draw() override {
    std::cout << "draw circle " << pos_.x_ << radius_ << std::endl;
  }
  std::string name() override { return "Circle"; }
  int radius() { return radius_; }
  void accept(IPrimitiveVisitor &v) override;

 private:
  int radius_;
};

/** @} */  // end of grapheditor

#endif  // PRIMITIVE_H
