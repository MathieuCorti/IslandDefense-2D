//
//  Boat.cpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <iostream>
#include "helpers/OpenGL.hpp"

#include "includes/Waves.hpp"
#include "includes/Boat.hpp"
#include "includes/Game.hpp"

Boat::Boat(float x, float cannonDelta, float cannonRotation, Color color, float speed) : 
  Movable(speed, x, 0), Alive(10, color), _cannonDelta(cannonDelta) {
  _cannon = std::make_shared<Cannon>(cannonRotation);
  for (auto& shape: _shapes) {
    shape.color = color;
  }
}

bool Boat::update() {
  _wavesHeight = Waves::computeHeight(_x);
  float x = _x;
  float y = _y + _wavesHeight;
  float x2 = 1;
  float y2 = Waves::computeSlope(x);
  float dot = x * x2 + y * y2;
  float det = x * y2 - y * x2;
  _angle = 180 + static_cast<float>(std::atan2(det, dot) * 180 / M_PI);
  return false;
}

void Boat::draw() const {
  for (auto shape: _shapes) {
    glPushMatrix();
    glTranslatef(_x, _y + _wavesHeight, 0);
    glRotatef(_angle, 0.0, 0.0, 1.0);
    glBegin(shape.mode);
    shape.applyColor();
    for (auto coordinates: shape.parts) {
      glVertex2d(coordinates.first, coordinates.second);
    }
    glEnd();
    glPopMatrix();
  }
  glPushMatrix();
  glTranslatef(_x, _y + _wavesHeight, 0);
  glRotatef(_angle, 0.0, 0.0, 1.0);
  _cannon->draw();
  glPopMatrix();
}

Cannon::Ptr Boat::getCannon() const {
  return _cannon;
}
