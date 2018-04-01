//
// Created by wilmot_g on 24/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"
#include "../helpers/Axes.hpp"
#include "Projectile.hpp"

class Cannon : public Displayable {
public:
  typedef std::shared_ptr<Cannon> Ptr;

  Cannon(float rotation = 1.0f, float speed = 3.0f, Color color = Color(0, 127, 255), bool inverted = false, float scale = 1.0f);

  void draw() const;

  void setPos(float x, float y, float angle);

  void speed(float value);

  void rotation(float angle);

  Projectile::Ptr blast();

private:
  void drawDirection() const;

  void drawTrajectory() const;

  float _rotation;
  float _speed;
  float _angle;
  float _scale;
  bool _inverted;
  Axes::Vec2f _velocity;
  float _lastFire;
  Color _color;
};