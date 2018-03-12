//
// Created by wilmot_g on 12/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"

class Waves : public Displayable {
public:
  void draw() const override;
  static float computeHeight(float x);
  static float computeSlope(float x);
private:
  void drawVector(float x, float y, float a, float b, float s, bool normalize, float red, float green, float blue) const;
};