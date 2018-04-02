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
    Movable(speed, x, 0), Alive(10), _cannonDelta(cannonDelta), _inverted(inverted), _lastWavesHeight(0) {
  _cannon = std::make_shared<Cannon>(cannonRotation, 3.0f, color, inverted);
  // HULL
  _shapes.push_back(Shape({
                            Coordinates(-0.05f, -0.025f),
                            Coordinates(0.05f, -0.025f),
                            Coordinates(0.1f, 0.025f),
                            Coordinates(-0.1f, 0.025f),
                          }, GL_POLYGON, _x, _y));
  // BRIDGE
  _shapes.push_back(Shape({
                            Coordinates(-0.025f, 0.025f),
                            Coordinates(0.025f, 0.025f),
                            Coordinates(0.025f, 0.065f),
                            Coordinates(-0.025f, 0.065f),
                          }, GL_POLYGON, _x, _y));
  for (auto &shape: _shapes) {
    shape.color = color;
  }
  _collidables.push_back(this);
  for (auto e : _cannon->getCollidables()) {
    _collidables.push_back(e);
  }
}

bool Boat::update() {
  if (getCurrentHealth() == 0) {
    return true;
  }

  float wavesHeight = Waves::computeHeight(_x);
  _y = _y - _lastWavesHeight + wavesHeight;
  _lastWavesHeight = wavesHeight;
  float x2 = 1;
  float y2 = Waves::computeSlope(_x);
  float dot = _x * x2 + _y * y2;
  float det = _x * y2 - _y * x2;
  _angle = static_cast<float>(std::atan2(det, dot) * 180 / M_PI);
  _cannon->setPos(_x, _y, _angle);
  return false;
}

void Boat::draw() const {
  for (auto shape: _shapes) {
    glPushMatrix();
    glTranslatef(_x, _y, 0);
//    glRotatef(_angle + (_inverted ? 0 : 180), 0.0, 0.0, 1.0);
    glBegin(shape.mode);
    shape.applyColor();
    for (auto coordinates: shape.parts) {
      glVertex2d(coordinates.x, coordinates.y);
    }
    glEnd();
    glPopMatrix();
  }
  _cannon->draw();

  for (auto &s : _shapes) {
    BoundingBox bb1 = s.getBoundingBox();

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    glVertex2d(bb1.lowerRight.x, bb1.lowerRight.y);
    glColor3f(0, 1, 0);
    glVertex2d(bb1.upperLeft.x, bb1.upperLeft.y);
    glEnd();

    std::cout << _y << "\t\t" << s._deltaY << "\t\t" << bb1.upperLeft.y << "\t" << bb1.lowerRight.y << std::endl;
  }
}

void Boat::move(Direction direction) {
  auto iShapes = Game::getInstance().getEntities()["island"]->_shapes;
  switch (direction) {
    case LEFT:
      setX(getX() - getSpeed());
      if (_x >= 0.95 || _x <= -0.95 || Shape::collide(iShapes, _shapes)) {
        setX(getX() + getSpeed());
      }
      break;
    case RIGHT:
      setX(getX() + getSpeed());
      if (_x >= 0.95 || _x <= -0.95|| Shape::collide(iShapes, _shapes)) {
        setX(getX() - getSpeed());
      }
      break;
    default:
      break;
  }
}

Cannon::Ptr Boat::getCannon() const {
  return _cannon;
}
