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

class Shape;
typedef std::list<Shape> Shapes;

class Displayable : public Entity {
public:
  typedef std::shared_ptr<Displayable> Ptr;

  Shapes _shapes = Shapes();

  explicit Displayable(float x = 0, float y = 0) : Entity(x, y) {}

  virtual void draw() const;

  virtual bool update() {
    return false;
  };
};