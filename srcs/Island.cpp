//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include "includes/Game.hpp"
#include "includes/Island.hpp"

// PUBLIC

Island::Island(const Color &color) : Displayable(color) {}

void Island::draw() const {
  glBegin(GL_POLYGON);
  glColor3f(color.r, color.g, color.b);
  glVertex2f(-0.3f, -1);
  glVertex2f(0.3f, -1);
  glVertex2f(0.3f, 0.3f);
  glVertex2f(-0.3f, 0.3f);
  glEnd();
}