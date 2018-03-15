//
// Created by wilmot_g on 12/03/18.
//

#pragma once

#include "OpenGL.hpp"
#include "Displayable.hpp"

class Axes : public Displayable {
public:
  void draw() const override {
    glBegin(GL_LINES);
    glColor3f(0, 1, 0);
    glVertex2f(0, 1);
    glVertex2f(0, 0);
    glColor3f(1, 0, 0);
    glVertex2f(1, 0);
    glVertex2f(0, 0);
    glColor3f(1, 1, 1);
    glVertex2f(1, 1);
    glVertex2f(-1, -1);
    glEnd();
  }
};