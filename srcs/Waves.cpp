//
// Created by wilmot_g on 12/03/18.
//

// PUBLIC

#include "helpers/Glut.hpp"
#include "includes/Waves.hpp"
#include <cmath>
#include <iostream>

float Waves::computeHeight(float x) {
  float amplitude = 0.3;
  float waveLength = 1;
  double k = 2 * M_PI / waveLength;
  return (float) (amplitude * sin(k * x));
}

float Waves::computeSlope(float x) {
  float amplitude = 0.3;
  float waveLength = 1;
  double k = 2 * M_PI / waveLength;
  return (float) (amplitude * k * cos(k * x));
}

void Waves::drawVector(float x, float y, float a, float b, float s, bool normalize, float red, float green,
                       float blue) const {
  float magnitude = std::sqrt(a * a + b * b);
  a = (normalize ? a / magnitude : a) * s;
  b = (normalize ? b / magnitude : b) * s;

  glColor3f(red, green, blue);
  glVertex2f(x, y);
  glVertex2f(x + a, y + b);
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

//    glBegin(GL_LINES);
//    glColor3f(1, 1, 1);
//    float dx = 1;
//    float dy = computeSlope(x);
//    drawVector(x, sinx, dx, dy, 0.1, true, 1, 0, 0); //Tangeant
//    drawVector(x, sinx, -dy, dx, 0.1, true, 0, 1, 0); //Normal
//    glEnd();

    glEnable(GL_BLEND);
    glBegin(GL_POLYGON);
    glColor4f(0, 0.5, 1, 0.5);
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
