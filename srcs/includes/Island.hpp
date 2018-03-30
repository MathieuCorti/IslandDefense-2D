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
  Island(const Color &color = Color(255, 255, 0));

  bool update() override { return false; }

  void draw() const override;
};