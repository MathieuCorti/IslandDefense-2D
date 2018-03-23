//
//  Boat.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include <list>

#include "../helpers/Movable.hpp"
#include "../helpers/Displayable.hpp"
#include "../helpers/DisplayableShape.hpp"

class Boat : public Displayable, public Movable {
private:
  DisplayableShapes _shapes = {
    // HULL
    DisplayableShape({
                       std::make_pair( -0.05 , -0.025 ),
                       std::make_pair( 0.05  , -0.025 ),
                       std::make_pair( 0.1   , 0.025  ),
                       std::make_pair( -0.1  , 0.025  ),
                     }, GL_POLYGON, Color(0, 0, 255)),
    // BRIDGE
    DisplayableShape({
                       std::make_pair( -0.025 , 0.025 ),
                       std::make_pair( 0.025  , 0.025 ),
                       std::make_pair( 0.025  , 0.065 ),
                       std::make_pair( -0.025 , 0.065 ),
                     }, GL_POLYGON, Color(0, 0, 255)),
  };

public:
  void draw() const override;
  Boat();
};

