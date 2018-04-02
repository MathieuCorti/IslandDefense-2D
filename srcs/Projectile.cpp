//
// Created by wilmot_g on 23/03/18.
//

#include "helpers/Glut.hpp"

#include <cmath>
#include "includes/Projectile.hpp"
#include "includes/Game.hpp"

#define PROJECTILE_DAMAGES 1

Projectile::Projectile(float t, float x, float y, Axes::Vec2f v, Color c) : Displayable(x, y),
                                                                            Alive(1),
                                                                            _color(c),
                                                                            _startT(t),
                                                                            _startX(x),
                                                                            _startY(y),
                                                                            _startVelocity(v),
                                                                            _velocity(v) {
  _collidables.push_back(this);
}

Shape Projectile::getCircle(float radius, float _x, float _y) {
  Shape shape;
  float x, y;

  shape.mode = GL_LINE_STRIP;
  x = static_cast<float>(radius * std::cos(359 * M_PI / 180.0f));
  y = static_cast<float>(radius * std::sin(359 * M_PI / 180.0f));
  shape.parts.emplace_back(_x + x, _y + y);
  for (int j = 0; j < 360; j++) {
    x = static_cast<float>(radius * std::cos(j * M_PI / 180.0f));
    y = static_cast<float>(radius * std::sin(j * M_PI / 180.0f));
    shape.parts.emplace_back(_x + x, _y + y);
  }
  return shape;
}

bool Projectile::update() {
  if (getCurrentHealth() == 0) {
    return true;
  }

  _shapes.clear();
  _shapes.push_back(getCircle(0.02f, _x, _y));
  float t = Game::getInstance().getTime() - _startT;
  _x = _startVelocity.x * t + _startX;
  _y = _startY + _startVelocity.y * t + g * t * t / 2.0f;

  std::cout << std::endl;
  auto entities = Game::getInstance().getEntities();                      //Get all entities
  for (auto &entityBag: entities) {                                       //Get one entity
    for (auto entity : entityBag.second->getCollidables()) {              //Get all the subentities
      if (entity != this) {                                               //Do not collide with yourself
        auto aliveEntity = dynamic_cast<Alive *>(entity);                 //Can it be collided with ?
        if (aliveEntity != nullptr) {
          for (auto &thisShape: _shapes) {                                //Get the shapes of the projectile
            for (auto &enemyShape: entity->getShapes()) {                 //Get the shapes of the subentity
              if (enemyShape.collideWith(thisShape)) {                    //Check collision
                aliveEntity->takeDamage(PROJECTILE_DAMAGES);              //Deal damage
                return true;                                              //Collision, remove projectile
              }
            }
          }
        }
      }
    }
  }

  return _y < -1 || _x < -1 || _x > 1;                                    //Out of bounds, remove projectile
}

void Projectile::draw() const {
  glColor3f(_color.r, _color.g, _color.b);
  for (auto shape : _shapes) {
    glBegin(shape.mode);
    for (auto coordinates: shape.parts) {
      glVertex2d(coordinates.x, coordinates.y);
    }
    glEnd();
  }

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

  for (auto &s : _shapes) {
    BoundingBox bb1 = s.getBoundingBox();

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    glVertex2d(bb1.lowerRight.x, bb1.lowerRight.y);
    glVertex2d(bb1.upperLeft.x, bb1.upperLeft.y);
    glEnd();
  }
}