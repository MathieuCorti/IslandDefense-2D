//
//  Displayable.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include "../helpers/Displayable.hpp"

class Island : public Displayable {
public:
  bool update() override { return false; }

  void draw() const override;
};