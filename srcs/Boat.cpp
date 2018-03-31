//
//  Boat.cpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <iostream>
#include "helpers/Glut.hpp"

#include "includes/Waves.hpp"
#include "includes/Boat.hpp"
#include "includes/Game.hpp"

Boat::Boat(float x, float cannonDelta, float cannonRotation, Color color, bool inverted, float speed) :
  Movable(speed, x, 0), Alive(10), _cannonDelta(cannonDelta), _inverted(inverted) {
  _cannon = std::make_shared<Cannon>(cannonRotation, 3.0f, color, inverted);
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
  _angle = static_cast<float>(std::atan2(det, dot) * 180 / M_PI);
  _cannon->setPos(_x, _y + _wavesHeight, _angle);
  return false;
}

void Boat::draw() const {
  for (auto shape: _shapes) {
    glPushMatrix();
    glTranslatef(_x, _y + _wavesHeight, 0);
    glRotatef(_angle + (_inverted ? 0 : 180), 0.0, 0.0, 1.0);
    glBegin(shape.mode);
    shape.applyColor();
    for (auto coordinates: shape.parts) {
      glVertex2d(coordinates.x, coordinates.y);
    }
    glEnd();
    glPopMatrix();
  }
  _cannon->draw();
}

Cannon::Ptr Boat::getCannon() const {
  return _cannon;
}
