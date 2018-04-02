//
//  Shape.hpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/16/18.
//

#pragma once

#include "Glut.hpp"

#include <list>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Displayable.hpp"
#include "Color.hpp"

struct Coordinates {
  Coordinates(float x, float y) : x(x), y(y) {}

  float x;
  float y;
};

struct BoundingBox {
  BoundingBox(const Coordinates &upperLeft, const Coordinates &lowerRight) : upperLeft(upperLeft),
                                                                             lowerRight(lowerRight) {}

  Coordinates upperLeft;
  Coordinates lowerRight;

  Coordinates center() {
    return {(upperLeft.x + lowerRight.x) / 2, (upperLeft.y + upperLeft.x) / 2};
  }
};

struct Shape {
private:
  
  constexpr static float defaultDelta = 0;
  const float& _deltaX;
  const float& _deltaY;
  
public:

  std::vector<Coordinates> parts;
  float size;
  GLenum mode;
  Color color;

  void applyColor() const {
    glColor4f(color.r, color.g, color.b, color.a);
  }

  explicit Shape(std::vector<Coordinates> parts = std::vector<Coordinates>(), GLenum mode = GL_POLYGON,
                  Color color = Color(1, 1, 1), const float& deltaX = defaultDelta, const float& deltaY = defaultDelta)
    : _deltaX(deltaX), _deltaY(deltaY), color(color), parts(std::move(parts)), mode(mode), size(1) {
  }

  explicit Shape(std::vector<Coordinates> parts, GLenum mode, const float& deltaX, const float& deltaY, 
                 Color color = Color(1, 1, 1))
    : _deltaX(deltaX), _deltaY(deltaY), color(color), parts(std::move(parts)), mode(mode), size(1) {
  }

  explicit Shape(const float& deltaX, const float& deltaY, std::vector<Coordinates> parts = std::vector<Coordinates>(),
                 GLenum mode = GL_POLYGON, Color color = Color(1, 1, 1))
    : _deltaX(deltaX), _deltaY(deltaY), color(color), parts(std::move(parts)), mode(mode), size(1) {
  }

  BoundingBox getBoundingBox() const {
    auto xExtremes = std::minmax_element(parts.begin(), parts.end(),
                                         [this](const Coordinates &lhs, const Coordinates &rhs) {
                                           return lhs.x + _deltaX > rhs.x + _deltaX;
                                         });
    auto yExtremes = std::minmax_element(parts.begin(), parts.end(),
                                         [this](const Coordinates &lhs, const Coordinates &rhs) {
                                           return lhs.y + _deltaY > rhs.y + _deltaY;
                                         });
    return BoundingBox(Coordinates(xExtremes.first->x + _deltaX, yExtremes.first->y + _deltaY),
                       Coordinates(xExtremes.second->x + _deltaX, yExtremes.second->y + _deltaX));
  }

  bool collideWith(BoundingBox bb) {
    BoundingBox bb1 = getBoundingBox();
    BoundingBox bb2 = bb;
    
    return bb1.upperLeft.x > bb2.lowerRight.x && bb1.lowerRight.x < bb2.upperLeft.x &&
           bb1.upperLeft.y > bb2.lowerRight.y && bb1.lowerRight.y < bb2.upperLeft.y;
  }

  bool collideWith(Shape shape) {
    return collideWith(shape.getBoundingBox());
  }

};

typedef std::list<Shape> Shapes;