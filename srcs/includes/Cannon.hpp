//
// Created by wilmot_g on 24/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"
#include "../helpers/Axes.hpp"

class Cannon : public Displayable, public Entity {
public:
  typedef std::shared_ptr<Cannon> Ptr;

  Cannon(float rotation = 1.0f, float speed = 3.0f);

  bool update() { return false; };

  void draw() const;

  void updateState();

  void speed(float value);

  void rotation(float angle);

  Displayable::Ptr blast() const;

private:
  void drawDirection() const;

  void drawTrajectory() const;

  float _rotation;
  float _speed;
  Axes::Vec2f _velocity;
};