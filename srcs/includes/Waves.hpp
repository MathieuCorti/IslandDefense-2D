//
// Created by wilmot_g on 12/03/18.
//

#pragma once

#include <vector>
#include "../helpers/Displayable.hpp"

class Waves : public Displayable {
public:
  Waves();

  typedef std::vector<std::tuple<float, float> > vertices;

  void draw() const override;

  static float computeHeight(float x);

  static float computeSlope(float x);

  void toggleTangeants();

  void toggleNormals();

  void toggleWireframe();

  void toggleAnimate();

  void doubleVertices();

  void halveSegments();

  bool update() override;

private:
  bool _showTangeant;
  bool _showNormal;
  bool _showWireframe;
  int _segments;
  float _range;
  vertices _vertices;

  static bool g_animate;
  static float g_time;
};