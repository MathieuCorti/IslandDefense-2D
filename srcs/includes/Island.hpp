//
//  Displayable.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include "../helpers/Displayable.hpp"

class Island : public Alive {
private:
  DisplayableShapes _shapes = {
    DisplayableShape({
                       Coordinates(-0.3f, -1),
                       Coordinates(0.3f, -1),
                       Coordinates(0.3f, 0.3f),
                       Coordinates(-0.3f, 0.3f),
                     }, GL_POLYGON)
  };

public:
  Island(const Color &color = Color(255, 255, 0));

  bool update() override { return false; }

  void draw() const override;
};