//
// Created by wilmot_g on 12/03/18.
//

// PUBLIC

#include <cmath>

#include "helpers/Glut.hpp"
#include "includes/Waves.hpp"
#include "includes/Game.hpp"

float Waves::computeHeight(float x) {
  float amplitude = 0.3;
  float waveLength = (float) M_PI / 4;
  float k = 2 * (float) M_PI / waveLength;
  return amplitude * std::sin(k * x + waveLength * Game::getInstance().getTime());
}

float Waves::computeSlope(float x) {
  float amplitude = 0.3;
  float waveLength = 1;
  float k = 2 * (float) M_PI / waveLength;
  return amplitude * k * std::cos(k * x + waveLength * Game::getInstance().getTime());
}

void Waves::draw() const {
  int segments = 50;
  int range = 2;
  float stepSize = (float) range / (float) segments;

  std::tuple<float, float> points[50];
  for (int i = 0; i <= segments; i++) {
    std::get<0>(points[i]) = -1 + i * stepSize;
    std::get<1>(points[i]) = computeHeight(std::get<0>(points[i]));
  }


  if (_showWireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  glEnable(GL_BLEND);
  glBegin(GL_QUAD_STRIP);
  glColor4f(color.r, color.g, color.b, color.a);
  for (auto p : points) {
    float x = std::get<0>(p);
    float y = std::get<1>(p);
    glVertex2f(x, -1);
    glVertex2f(x, y);
  }
  glEnd();
  glDisable(GL_BLEND);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  if (_showTangeant || _showNormal)
    for (auto p : points) {
      float x = std::get<0>(p);
      float y = std::get<1>(p);
      float dx = 1;
      float dy = computeSlope(x);
      glBegin(GL_LINES);
      if (_showTangeant) {
        Axes::drawVector(x, y, dx, dy, 0.1, true, 1, 0, 0);
      }
      if (_showNormal) {
        Axes::drawVector(x, y, -dy, dx, 0.1, true, 0, 1, 0);
      }
      glEnd();
    }
}

void Waves::toggleTangeants() {
  _showTangeant = !_showTangeant;
}

void Waves::toggleNormals() {
  _showNormal = !_showNormal;
}

void Waves::toggleWireframe() {
  _showWireframe = !_showWireframe;
}

Waves::Waves(const Color &color) : Displayable(color) {
  
}
