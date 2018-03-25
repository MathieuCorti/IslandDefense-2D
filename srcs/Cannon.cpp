//
// Created by wilmot_g on 24/03/18.
//

#include "helpers/Glut.hpp"

#include "includes/Cannon.hpp"
#include "includes/Projectile.hpp"
#include "includes/Game.hpp"

const float g = -9.8f;

Cannon::Cannon(float rotation, float speed): _rotation(rotation), _speed(speed) {
  updateState();
}

void Cannon::drawDirection() const {
  glBegin(GL_LINES);
  Axes::drawVector(_x, _y, _velocity.x, _velocity.y, 0.5, true, 1, 0, 1);
  glEnd();
}

void Cannon::drawTrajectory() const {
  glBegin(GL_LINE_STRIP);
  glColor3f(0, 0.5, 1);

  float t = 0;
  for (;;) {
    float x = _x + _velocity.x * t;
    float y = _y + _velocity.y * t + g * t * t / 2.0f;

    if (y < -1 || x > 1 || x < -1) {
      break;
    }

    glVertex2f(x, y);
    t += 0.01;
  }
  glEnd();
}

Displayable::Ptr Cannon::blast() const {
  return std::make_shared<Projectile>(Game::getInstance().getTime(), _x, _y, _velocity);
}

void Cannon::update(float x, float y) {
  _x = x, _y = y;
}

void Cannon::draw() const {
  glColor3f(1, 1, 1);
  drawDirection();
  drawTrajectory();
}

void Cannon::updateState() {
  _velocity.x = std::cos(_rotation) * _speed;
  _velocity.y = std::sin(_rotation) * _speed;
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
