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
  void draw() const override;
};