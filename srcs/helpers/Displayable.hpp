//
//  Displayable.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include <memory>
#include "Entity.hpp"
#include "Color.hpp"
#include "Shape.hpp"

class Displayable : public Entity {
public:
  typedef std::shared_ptr<Displayable> Ptr;
 
  Shapes _shapes = Shapes();

  Displayable(float x = 0, float y = 0) : Entity(x, y) {}

  virtual void draw() const {
    for (Shape shape: _shapes) {
      glBegin(shape.mode);
      shape.applyColor();
      for (Coordinates coordinates: shape.parts) {
        glVertex2d(coordinates.x + _x, coordinates.y + _y);
      }
      glEnd();
    }
  }

  virtual bool update() {
    return false;
  };
};