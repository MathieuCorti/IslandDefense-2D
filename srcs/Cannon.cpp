//
// Created by wilmot_g on 24/03/18.
//

#include "helpers/Glut.hpp"

#include "includes/Cannon.hpp"
#include "includes/Projectile.hpp"
#include "includes/Game.hpp"

const float g = -9.8f;

Cannon::Cannon(float rotation, float speed, Color color): Displayable(color), _rotation(rotation), _speed(speed) {
  _angle = 0;
}

void Cannon::drawDirection() const {
  glBegin(GL_LINES);
  float x = _velocity.x;
  float y = _velocity.y;
  Axes::drawVector(0, 0, x, y, 0.5, true, 1, 0, 1);
  glEnd();
}

void Cannon::drawTrajectory() const {
  glBegin(GL_LINE_STRIP);
  glColor3f(0, 0.5, 1);

  float t = 0;
  for (;;) {
    float x = _velocity.x * t;
    float y = _velocity.y * t + g * t * t / 2.0f;

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

void Cannon::draw() const {
  glPushMatrix();
  glTranslatef(_x, _y, 0);
  glColor3f(1, 1, 1);
  drawDirection();
  drawTrajectory();
  glPopMatrix();
}

void Cannon::speed(float value) {
  _speed += value;
  _speed = _speed < 0 ? 0 : _speed;
}

void Cannon::rotation(float angle) {
  _rotation += angle;
}

void Cannon::setPos(float x, float y, float angle) {
  _x = x;
  _y = y;
  _angle = angle;
  _velocity.x = static_cast<float>(std::cos(_rotation + _angle * M_PI / 180) * _speed);
  _velocity.y = static_cast<float>(std::sin(_rotation + _angle * M_PI / 180) * _speed);
}
