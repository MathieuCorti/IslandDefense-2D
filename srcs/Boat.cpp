//
//  Boat.cpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <iostream>
#include "helpers/OpenGL.hpp"
#include "helpers/Glut.hpp"

#include "includes/Waves.hpp"
#include "includes/Boat.hpp"

Boat::Boat() {
  _x = 0;
  _y = 0;
  _speed = 0.01;
}

void Boat::draw() const {
  for (auto shape: _shapes) {
    glPushMatrix();
    glRotatef(Waves::computeSlope(_x), 0.0, 0.0, 1.0);

    glBegin(shape.mode);
    shape.applyColor();
    for (auto coordinates: shape.parts) {
      glVertex2d(_x + coordinates.first, _y + Waves::computeHeight(_x) + coordinates.second);
    }
    glEnd();

    glPopMatrix();
  }
}