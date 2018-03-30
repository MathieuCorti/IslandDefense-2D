//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include "includes/Game.hpp"
#include "includes/Island.hpp"

// PUBLIC

void Island::draw() const {
  for (auto& shape: _shapes) {
    shape.draw();
  }
}

Island::Island(const Color &color) : Alive(100, color) {
  for (auto& shape: _shapes) {
    shape.color = color;
  }
}
