//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include "helpers/Game.hpp"
#include "helpers/Island.hpp"

// PUBLIC

void Island::draw() const {
  glBegin(GL_POLYGON);
  gluLookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);
  glColor3f(1, 1, 0);
  glVertex3f(-3, -10, 0);
  glVertex3f(3, -10, 0);
  glVertex3f(3, 3, 0);
  glVertex3f(-3, 3, 0);
  glEnd();
}
