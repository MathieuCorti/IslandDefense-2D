//
// Created by wilmot_g on 12/03/18.
//

// PUBLIC

#include <cmath>

#include "helpers/Glut.hpp"
#include "includes/Waves.hpp"
#include "includes/Game.hpp"
#include "helpers/Axes.hpp"

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

void Waves::displayLogs(const float x, const float sinx) const {
  glBegin(GL_LINES);
  float dx = 1;
  float dy = computeSlope(x);
  Axes::drawVector(x, sinx, dx, dy, 0.1, true, 1, 0, 0); //Tangeant
  Axes::drawVector(x, sinx, -dy, dx, 0.1, true, 0, 1, 0); //Normal
  glEnd();
}

bool Waves::update() {
  return false;
}

void Waves::draw() const {
  int segments = 50;
  int range = 2;
  float stepSize = (float) range / (float) segments;

  for (int i = 0; i <= segments; i++) {
    float x = -1 + i * stepSize;
    float x2 = -1 + (i + 1) * stepSize;
    float sinx = computeHeight(x);
    float sinx2 = computeHeight(x2);

//    displayLogs(x, sinx);

    glEnable(GL_BLEND);
    glBegin(GL_POLYGON);
    glColor4f(color.r, color.g, color.b, color.a);
    glVertex2f(x, -1);
    glVertex2f(x, sinx);
    glVertex2f(x, sinx);
    glVertex2f(x2, sinx2);
    glVertex2f(x2, sinx2);
    glVertex2f(x2, -1);
    glVertex2f(x2, -1);
    glVertex2f(x, -1);
    glEnd();
    glDisable(GL_BLEND);
  }
}

Waves::Waves(const Color &color) : Displayable(color) {
  
}
