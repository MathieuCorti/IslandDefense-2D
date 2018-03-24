//
// Created by wilmot_g on 24/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"
#include "../helpers/Axes.hpp"

class Cannon : public Displayable {
public:

  //TYPEDEF:
  typedef struct {
    Axes::Vec2f pos, velocity;
  } State;

  Cannon();

  void draw() const;

  void updateState();

  void speed(float value);

  void rotation(float angle);

  float getRotation() const;

  float getSpeed() const;

private:
  float computeHeight(float) const;
  void drawDirection() const;
  void drawTrajectory() const;

  float _rotation;
  float _speed;
  State _state;
};