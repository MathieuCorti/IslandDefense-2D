//
// Created by wilmot_g on 01/04/18.
//

#pragma once

#include "../helpers/Axes.hpp"
#include "Cannon.hpp"
#include "../helpers/Alive.hpp"

class Cannon;

class Pellet : public Displayable, public Alive {
public:
  //Typedef
  typedef std::shared_ptr<Pellet> Ptr;

  explicit Pellet(float, float, float, Cannon *cannon, Color c = Color(255, 0, 0));

  bool update() override;

  void draw() const override;

private:
  float _radius;
  Color _color;
  float _startT;
  Cannon *_cannon;
};