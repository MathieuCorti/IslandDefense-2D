//
// Created by wilmot_g on 23/03/18.
//

#pragma once

#include <cmath>
#include <iostream>
#include <cmath>
#include "../helpers/Displayable.hpp"
#include "../helpers/Axes.hpp"
#include "Cannon.hpp"

extern const float g;

class Projectile : public Displayable {
public:
  explicit Projectile(Cannon::State);

  void draw() const;

  void updatePosition(float);

  float computeHeight(float) const;

  void update();

private:
  void drawCircle(float) const;

  Cannon::State _startState;
  Cannon::State _currentState;
};