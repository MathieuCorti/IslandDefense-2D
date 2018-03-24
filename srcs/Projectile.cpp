//
// Created by wilmot_g on 23/03/18.
//

#include "helpers/Glut.hpp"

#include <cmath>
#include "includes/Projectile.hpp"

Projectile::Projectile(Cannon::State state) : _startState(state), _currentState(state) {}

void Projectile::drawCircle(float radius) const {
  float x, y;

  glBegin(GL_LINES);
  x = static_cast<float>(radius * cos(359 * M_PI / 180.0f));
  y = static_cast<float>(radius * sin(359 * M_PI / 180.0f));
  for (int j = 0; j < 360; j++) {
    glVertex2f(x, y);
    x = static_cast<float>(radius * cos(j * M_PI / 180.0f));
    y = static_cast<float>(radius * sin(j * M_PI / 180.0f));
    glVertex2f(x, y);
  }
  glEnd();
}

void Projectile::updatePosition(float t) {
  _currentState.pos.x = _startState.velocity.x * t + _startState.pos.x;
  _currentState.pos.y = static_cast<float>(1.0 / 2.0 * g * t * t + _startState.velocity.y * t + _startState.pos.y);
}

float Projectile::computeHeight(float t) const {
  Axes::Vec2f r0 = _startState.pos;
  Axes::Vec2f v0 = _startState.velocity;

  return static_cast<float>(1.0 / 2.0 * g * t * t + v0.y * t + r0.y);
}

void Projectile::draw() const {
  glColor3f(1, 1, 1);
  drawCircle(0.1f);
}

void Projectile::update() {

}