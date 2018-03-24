//
// Created by wilmot_g on 24/03/18.
//

#include <GL/gl.h>
#include "includes/Cannon.hpp"
#include "includes/Projectile.hpp"

const float g = -9.8f;

Cannon::Cannon() {
  _state = {
      {0.0, 0.0},
      {0.0, 0.0}
  };
  _rotation = 0.0f;
  _speed = 1.0f;
}

float Cannon::computeHeight(float x) const {
//  return -12 * g * t2 + vy0 * t + y0;
  return static_cast<float>(1.0 / 2.0 * g * x * x + _state.velocity.y * x + _state.pos.y);
}

void Cannon::drawTrajectory() const {
  int segments = 100;
  int range = 2;
  float stepSize = (float) range / (float) segments;

  glEnable(GL_BLEND);
  glBegin(GL_LINE_STRIP);
  glColor3f(0, 0.5, 1);
  for (int i = 0; true; i++) {
    float x = i * stepSize;
    float y = computeHeight(x);

    if (y < 0) {
      break;
    }
    glVertex2f(x, y);
  }
  glEnd();
  glDisable(GL_BLEND);

}

void Cannon::draw() const {
  glColor3f(1, 1, 1);
  drawDirection();
  drawTrajectory();
}

void Cannon::drawDirection() const {
  glBegin(GL_LINES);
  Axes::drawVector(_state.pos.x, _state.pos.y, _state.velocity.x, _state.velocity.y, 0.5, true, 1, 0, 1);
  glEnd();
}

void Cannon::updateState() {
  _state.velocity.x = std::cos(_rotation * _speed);
  _state.velocity.y = std::sin(_rotation * _speed);
  std::cout << "x : " << _state.velocity.x << std::endl;
  std::cout << "y : " << _state.velocity.y << std::endl;
  std::cout << "x2 : " << _state.pos.x << std::endl;
  std::cout << "y2 : " << _state.pos.y << std::endl;
}

void Cannon::speed(float value) {
  _speed += value;
  _speed = _speed < 0 ? 0 : _speed;
  updateState();
}

void Cannon::rotation(float angle) {
  _rotation += angle;
  updateState();
}

float Cannon::getRotation() const {
  return _rotation;
}

float Cannon::getSpeed() const {
  return _speed;
}
