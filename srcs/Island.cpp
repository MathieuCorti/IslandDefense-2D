//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include "includes/Game.hpp"
#include "includes/Island.hpp"

// PUBLIC

Island::Island(Color color) : Alive(100) {
  _shapes.push_back(Shape({
                              Coordinates(-0.3f, -1),
                              Coordinates(0.3f, -1),
                              Coordinates(0.3f, 0.3f),
                              Coordinates(-0.3f, 0.3f),
                          }, GL_POLYGON, _x, _y));
  _cannon = std::make_shared<Cannon>(-3 * M_PI / 2, 3.0f, color, true, 2);
  for (auto &shape: _shapes) {
    shape.color = color;
  }
  _collidables.push_back(this);
}

void Island::draw() const {
  for (auto shape: _shapes) {
    glBegin(shape.mode);
    shape.applyColor();
    for (auto coordinates: shape.parts) {
      glVertex2d(coordinates.x, coordinates.y);
    }
    glEnd();
  }
  _cannon->draw();
}

bool Island::update() {
  _cannon->setPos(_x, _y + 0.3f, 0.0f);
  return false;
}

Cannon::Ptr Island::getCannon() const {
  return _cannon;
}