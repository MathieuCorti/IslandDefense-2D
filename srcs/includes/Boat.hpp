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

public:
  Shapes _shapes = {
    // HULL
    Shape({
            Coordinates(-0.05, -0.025),
            Coordinates(0.05, -0.025),
            Coordinates(0.1, 0.025),
            Coordinates(-0.1, 0.025),
          }, GL_POLYGON),
    // BRIDGE
    Shape({
            Coordinates(-0.025, 0.025),
            Coordinates(0.025, 0.025),
            Coordinates(0.025, 0.065),
            Coordinates(-0.025, 0.065),
          }, GL_POLYGON),
  };
  void draw() const;

  bool update();

  Boat(float x, float cannonDelta, float cannonRotation, Color color, bool inverted = false, float speed = 0.01);

  Cannon::Ptr getCannon() const;

  Cannon::Ptr _cannon;
  float _wavesHeight = 0;
  float _angle = 0;
  bool _inverted;
};

