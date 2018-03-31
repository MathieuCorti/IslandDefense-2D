//
//  Displayable.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include "../helpers/Displayable.hpp"
#include "../helpers/Alive.hpp"

class Island : public Alive, public Displayable {
public:
  Island(Color color);
};