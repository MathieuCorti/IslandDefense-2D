//
// Created by wilmot_g on 12/03/18.
//

// PUBLIC

#include <cmath>

#include "helpers/Glut.hpp"
#include "includes/Waves.hpp"
#include "includes/Game.hpp"

bool Waves::g_animate = true;
float Waves::g_time = 0;

Waves::Waves() {
  _showWireframe = false;
  _showNormal = false;
  _showTangeant = false;
  _segments = 64;
  _range = 2.0f;
}

float Waves::computeHeight(float x) {
  float amplitude = 0.3;
  float waveLength = (float) M_PI / 4;
  float k = 2 * (float) M_PI / waveLength;
  float shift = waveLength * Waves::g_time;
  return amplitude * std::sin(k * x + shift);
}

float Waves::computeSlope(float x) {
  float amplitude = 0.3;
  float waveLength = (float) M_PI / 4;
  float k = 2 * (float) M_PI / waveLength;
  float shift = waveLength * Waves::g_time;
  return amplitude * k * std::cos(k * x + shift);
}

bool Waves::update() {
  if (Waves::g_animate || (_segments >= 64 && _vertices.empty()) || _segments < 64) {
    _vertices.clear();
    for (int i = 0; i <= _segments; i++) {
      float stepSize = _range / (float) _segments;
      float x = -1 + i * stepSize;
      float y = computeHeight(x);
      _vertices.push_back(std::make_tuple(x, y));
    }
  }
  if (Waves::g_animate) {
    Waves::g_time += Game::getInstance().getDeltaTime();
  }
  return false;
}

void Waves::draw() const {
  if (_showWireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  glEnable(GL_BLEND);
  glBegin(GL_QUAD_STRIP);
  glColor4f(0, 0.5, 1, 0.5);
  for (auto p : _vertices) {
    float x = std::get<0>(p);
    float y = std::get<1>(p);
    glVertex2f(x, -1);
    glVertex2f(x, y);
  }
  glEnd();
  glDisable(GL_BLEND);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  if (_showTangeant || _showNormal)
    for (auto p : _vertices) {
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

void Waves::toggleAnimate() {
  Waves::g_animate = !Waves::g_animate;
}

void Waves::doubleVertices() {
  _segments *= 2;
  _vertices.clear();
}

void Waves::halveSegments() {
  _segments /= 2;
  _segments = _segments < 4 ? 4 : _segments;
  _vertices.clear();
}

