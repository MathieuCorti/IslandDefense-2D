//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include "includes/Game.hpp"
#include "includes/Island.hpp"

// PUBLIC

void Island::draw() const {
  gluLookAt(_x, _y, -10, _x, _y, 0, 0, 1, 0);

  glBegin(GL_POLYGON);
  glColor3f(1, 1, 0);
  glVertex3f(-3, -10, 0);
  glVertex3f(3, -10, 0);
  glVertex3f(3, 3, 0);
  glVertex3f(-3, 3, 0);
  glEnd();
}
