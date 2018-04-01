//
// Created by wilmot_g on 24/03/18.
//

#include "helpers/Glut.hpp"

#include "includes/Cannon.hpp"
#include "includes/Game.hpp"

const float g = -9.8f;

Cannon::Cannon(float rotation, float speed, Color color, bool inverted, float scale) : _color(color),
                                                                                       _rotation(rotation),
                                                                                       _speed(speed),
                                                                                       _inverted(inverted),
                                                                                       _scale(scale) {
  _angle = 0;
  _lastFire = 0;
}

void Cannon::drawDirection() const {
  glPushMatrix();
  glTranslatef(_x, _y, 0);
  glRotatef(static_cast<GLfloat>(_angle + _rotation * 180 / M_PI - 90), 0.0, 0.0, 1.0);

  glBegin(GL_POLYGON);
  glVertex2f(-0.01f * _scale, 0.0f * _scale);
  glVertex2f(-0.01f * _scale, 0.1f * _scale);
  glVertex2f(0.01f * _scale, 0.1f * _scale);
  glVertex2f(0.01f * _scale, 0.0f * _scale);
  glEnd();
  glPopMatrix();
}

void Cannon::drawTrajectory() const {
  glBegin(GL_LINE_STRIP);

  float t = 0;
  for (;;) {
    float x = _x + _velocity.x * t + _velocity.x / 30;
    float y = _y + _velocity.y * t + g * t * t / 2.0f + _velocity.y / 30;

    if (y < -1 || x > 1 || x < -1) {
      break;
    }

    glVertex2f(x, y);
    t += 0.01;
  }
  glEnd();
}

Projectile::Ptr Cannon::blast() {
  if (Game::getInstance().getTime() - _lastFire > 1.0f / SPEED) {
    _lastFire = Game::getInstance().getTime();
    return std::make_shared<Projectile>(Game::getInstance().getTime(), _x + _velocity.x / 30, _y + _velocity.y / 30,
                                        _velocity, _color);
  }
  return nullptr;
}

void Cannon::draw() const {
  glPushMatrix();
  drawTrajectory();
  drawDirection();
  glPopMatrix();
}

void Cannon::speed(float value) {
  _speed += value;
  _speed = _speed < 0 ? 0 : _speed;
}

void Cannon::rotation(float angle) {
  _rotation += angle;
  _rotation = static_cast<float>(_rotation < (_inverted ? -2 * M_PI : 0) ? (_inverted ? -2 * M_PI : 0) : _rotation);
  _rotation = static_cast<float>(_rotation > (_inverted ? -M_PI : M_PI) ? (_inverted ? -M_PI : M_PI) : _rotation);
}

void Cannon::setPos(float x, float y, float angle) {
  _x = x;
  _y = y;
  _angle = angle + (_inverted ? 0 : 180);
  _velocity.x = static_cast<float>(std::cos(_rotation + _angle * M_PI / 180.0f) * _speed);
  _velocity.y = static_cast<float>(std::sin(_rotation + _angle * M_PI / 180.0f) * _speed);
}
