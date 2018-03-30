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

class Displayable {

public:
  typedef std::shared_ptr<Displayable> Ptr;

  Color color;

  Displayable(const Color &color) : color(color) {}

  virtual void draw() const = 0;

  virtual bool update() = 0;
};