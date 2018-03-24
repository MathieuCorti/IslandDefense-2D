//
//  DisplayableShape.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/16/18.
//

#pragma once

#include "Glut.hpp"

#include <utility>
#include <vector>

#include "Displayable.hpp"
#include "Color.hpp"

struct DisplayableShape : Displayable {
public:
  typedef std::pair<float, float> Coordinates;

  std::vector<Coordinates> parts;
  float size;
  GLenum mode;
  Color color;

  void applyColor() const {
    glColor4f(color.r, color.g, color.b, color.a);
  }

  bool update() override {}

  void draw() const override {
    glBegin(mode);
    applyColor();
    for (Coordinates coordinates: parts) {
      glVertex2d(coordinates.first, coordinates.second);
    }
    glEnd();
  }

  DisplayableShape(std::vector<Coordinates> parts = std::vector<Coordinates>(), GLenum mode = GL_POLYGON,
                   Color color = Color(1, 1, 1)) :
      parts(parts), mode(mode), color(color), size(1) {
  }
};

typedef std::list<DisplayableShape> DisplayableShapes;