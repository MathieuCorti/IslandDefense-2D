//
//  Displayable.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include <memory>
#include "Entity.hpp"

class Displayable {
public:
  typedef std::shared_ptr<Displayable> Ptr;

  virtual void draw() const = 0;

  virtual bool update() {
    return false;
  };
};