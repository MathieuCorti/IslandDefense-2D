//
// Created by wilmot_g on 01/04/18.
//

#include <utility>
#include "includes/Pellet.hpp"
#include "includes/Game.hpp"

Pellet::Pellet(float t, float x, float y, Cannon *cannon, Color c) : Displayable(x, y),
                                                                     _color(c),
                                                                     _startT(t),
                                                                     _radius(0),
                                                                     _cannon(cannon) {}

bool Pellet::update() {
  _x = _cannon->getX() + _cannon->getVelocity().x / 20 * _cannon->getScale();
  _y = _cannon->getY() + _cannon->getVelocity().y / 20 * _cannon->getScale();
  float x = Game::getInstance().getTime() - _startT;
  _radius += 0.00008 / x;
  std::cout << _radius << std::endl;
  return _radius > 0.2f / SPEED;
}

void Pellet::draw() const {
  glColor3f(_color.r, _color.g, _color.b);
  Projectile::drawCircle(_radius, _x, _y);
}
