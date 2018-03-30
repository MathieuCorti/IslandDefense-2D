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
  _wavesRotation = Waves::computeSlope(_x);
  _cannon->update(_x + _cannonDelta, _y + _wavesHeight);
  return false;
}

void Boat::draw() const {
  for (auto shape: _shapes) {
    glPushMatrix();
    glRotatef(_wavesRotation, 0.0, 0.0, 1.0);

    glBegin(shape.mode);
    shape.applyColor();
    for (auto coordinates: shape.parts) {
      glVertex2d(_x + coordinates.first, _y + _wavesHeight + coordinates.second);
    }
    glEnd();

    glPopMatrix();
  }

  _cannon->draw();
}

Cannon::Ptr Boat::getCannon() const {
  return _cannon;
}
