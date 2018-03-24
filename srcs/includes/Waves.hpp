//
// Created by wilmot_g on 12/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"

class Waves : public Displayable {
public:
  bool update() override;

  void draw() const override;

  void displayLogs(float x, const float sinx) const;

  static float computeHeight(float x);

  static float computeSlope(float x);

private:
};