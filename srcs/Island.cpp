//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include "includes/Game.hpp"
#include "includes/Island.hpp"

// PUBLIC

Island::Island(Color color) : Alive(100) {
  _shapes.push_back(Shape({
                            Coordinates(-0.3f, -1),
                            Coordinates(0.3f, -1),
                            Coordinates(0.3f, 0.3f),
                            Coordinates(-0.3f, 0.3f),
                          }, GL_POLYGON));
  for (auto& shape: _shapes) {
    shape.color = color;
  }
}
