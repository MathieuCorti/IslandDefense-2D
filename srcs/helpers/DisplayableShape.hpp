//
//  DisplayableShape.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/16/18.
//

#pragma once

#include "Glut.hpp"

#include <list>
#include <utility>
#include <vector>

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
};

struct DisplayableShape : Displayable {
public:

  std::vector<Coordinates> parts;
  float size;
  GLenum mode;

  void applyColor() const {
    glColor4f(color.r, color.g, color.b, color.a);
  }

  bool update() override { return false; }

  void draw() const override {
    glBegin(mode);
    applyColor();
    for (Coordinates coordinates: parts) {
      glVertex2d(coordinates.x, coordinates.y);
    }
    glEnd();
  }

  DisplayableShape(std::vector<Coordinates> parts = std::vector<Coordinates>(), GLenum mode = GL_POLYGON,
                   Color color = Color(1, 1, 1)) : Displayable(color),
      parts(parts), mode(mode), size(1) {
  }
  
  BoundingBox getBoundingBox() {
    auto xExtremes = std::minmax_element(parts.begin(), parts.end(),
                                         [](const Coordinates& lhs, const Coordinates& rhs) {
                                           return lhs.x < rhs.x;
                                         });
    auto yExtremes = std::minmax_element(parts.begin(), parts.end(),
                                         [](const Coordinates& lhs, const Coordinates& rhs) {
                                           return lhs.y < rhs.y;
                                         });

    return BoundingBox(Coordinates(xExtremes.first->x, yExtremes.first->y),
                       Coordinates(xExtremes.second->x, yExtremes.second->y));
  }
  
  bool collideWith(BoundingBox bb) {
    BoundingBox bb1 = getBoundingBox();
    BoundingBox bb2 = bb;

    return bb1.upperLeft.x < bb2.lowerRight.x && bb1.lowerRight.x > bb2.upperLeft.x &&
           bb1.upperLeft.y > bb2.lowerRight.y && bb1.lowerRight.y < bb2.upperLeft.y;
  }
 
  bool collideWith(DisplayableShape shape) {
    return collideWith(shape.getBoundingBox());
  }

};

typedef std::list<DisplayableShape> DisplayableShapes;