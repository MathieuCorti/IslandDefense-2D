//
// Created by wilmot_g on 23/03/18.
//

#include "helpers/Glut.hpp"

#include <cmath>
#include "includes/Projectile.hpp"
#include "includes/Game.hpp"

Projectile::Projectile(float t, float x, float y, Axes::Vec2f v) : Entity(x, y, 0), _startT(t), _startX(x), _startY(y),
                                                                   _startVelocity(v), _velocity(v) {}

void Projectile::drawCircle(float radius) const {
  float x, y;

  glBegin(GL_LINES);
  x = static_cast<float>(radius * cos(359 * M_PI / 180.0f));
  y = static_cast<float>(radius * sin(359 * M_PI / 180.0f));
  for (int j = 0; j < 360; j++) {
    glVertex2f(_x + x, _y + y);
    x = static_cast<float>(radius * cos(j * M_PI / 180.0f));
    y = static_cast<float>(radius * sin(j * M_PI / 180.0f));
    glVertex2f(_x + x, _y + y);
  }
  glEnd();
}

bool Projectile::update() {
  float t = Game::getInstance().getTime() - _startT;
  _x = _startVelocity.x * t + _startX;
  _y = _startY + _startVelocity.y * t + g * t * t / 2.0f;
  return _y < -1 || _x < -1 || _x > 1;
}

void Projectile::draw() const {
  glColor3f(1, 0, 0);
  drawCircle(0.01f);
}