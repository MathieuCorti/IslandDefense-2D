//
// Created by wilmot_g on 23/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"

class Stats : public Displayable {
private:
  Color _color;

public:
  Stats(const Color &color = Color(255, 255, 0));

  bool update() override { return false; }
  
  void draw() const override;
};