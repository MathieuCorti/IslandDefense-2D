//
// Created by wilmot_g on 23/03/18.
//

#pragma once

#include <cmath>
#include <iostream>
#include <cmath>
#include "../helpers/Displayable.hpp"
#include "../helpers/Axes.hpp"

extern const float g;

class Projectile : public Displayable {
public:
  //Typedef
  typedef std::shared_ptr<Projectile> Ptr;

  explicit Projectile(float, float, float, Axes::Vec2f, Color c = Color(255, 0, 0));

  bool update() override;

  void draw() const override;

  static Shape getCircle(float, float, float);

  Shapes _shapes;

private:
  Color _color;
  float _startT, _startX, _startY;
  Axes::Vec2f _startVelocity, _velocity;
};