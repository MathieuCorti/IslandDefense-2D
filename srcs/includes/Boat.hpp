//
//  Boat.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include <list>

#include "../helpers/Alive.hpp"
#include "../helpers/Movable.hpp"
#include "../helpers/Displayable.hpp"
#include "../helpers/Shape.hpp"
#include "Cannon.hpp"

class Boat : public Movable, public Alive {
private:
  float _cannonDelta;
  float _lastWavesHeight;
  Cannon::Ptr _cannon;
  float _angle;
  bool _inverted;

public:
  void draw() const override;

  bool update() override;

  void move(Direction direction) override;

  Boat(float x, float cannonDelta, float cannonRotation, Color color, bool inverted = false, float speed = 0.01);

  Cannon::Ptr getCannon() const;
};

