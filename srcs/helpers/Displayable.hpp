//
//  Displayable.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include "Entity.hpp"

class Displayable : public Entity {
public:
  virtual void draw() const = 0;
};