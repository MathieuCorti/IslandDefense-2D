//
// Created by wilmot_g on 12/03/18.
//

#pragma once

#include "../helpers/Displayable.hpp"

class Waves : public Displayable {
public:
  Waves(const Color &color = Color(0, 127, 255, 0.5));

  bool update() override;

  void draw() const override;

  static float computeHeight(float x);

  static float computeSlope(float x);

  void toggleTangeants();

  void toggleNormals();

  void toggleWireframe();

private:
  bool _showTangeant;
  bool _showNormal;
  bool _showWireframe;
};