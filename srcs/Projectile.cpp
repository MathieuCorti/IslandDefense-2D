//
// Created by wilmot_g on 23/03/18.
//

#include "helpers/Glut.hpp"

#include <cmath>
#include "includes/Projectile.hpp"
#include "includes/Game.hpp"

Projectile::Projectile(float t, float x, float y, Axes::Vec2f v, Color c) : Displayable(c), Entity(x, y, 0),
                                                                   _startT(t), _startX(x), _startY(y),
                                                                   _startVelocity(v), _velocity(v) {}

void Projectile::drawCircle(float radius) const {
  float x, y;

  glBegin(GL_LINE_STRIP);
  x = static_cast<float>(radius * std::cos(359 * M_PI / 180.0f));
  y = static_cast<float>(radius * std::sin(359 * M_PI / 180.0f));
  glVertex2f(_x + x, _y + y);
  for (int j = 0; j < 360; j++) {
    x = static_cast<float>(radius * std::cos(j * M_PI / 180.0f));
    y = static_cast<float>(radius * std::sin(j * M_PI / 180.0f));
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
  glColor3f(color.r, color.g, color.b);
  drawCircle(0.02f);

  int segments = 64;
  float t = Game::getInstance().getTime() - _startT;
  glColor3f(1, 1, 1);
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i <= segments; i++) {
    float tx = (float) i * t / (float) segments;
    float x = _startVelocity.x * tx + _startX;
    float y = _startY + _startVelocity.y * tx + g * tx * tx / 2.0f;
    glVertex2f(x, y);
  }
  glEnd();

}