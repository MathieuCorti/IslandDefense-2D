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

class Projectile : public Displayable, public Entity {
public:
  explicit Projectile(float, float, float, Axes::Vec2f);

  bool update() override;

  void draw() const;

private:
  void drawCircle(float) const;

  float _startT, _startX, _startY;
  Axes::Vec2f _startVelocity, _velocity;
};