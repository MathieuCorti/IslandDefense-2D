//
// Created by wilmot_g on 12/03/18.
//

// PUBLIC

#include <GL/glu.h>
#include "includes/Waves.h"

void Waves::draw() const {
  gluLookAt(_x, _y, -10, _x, _y, 0, 0, 1, 0);

  glBegin(GL_LINES);
  glColor3f(0, 1, 0);
  glVertex3f(0, 5, 0);
  glColor3f(1, 0, 0);
  glVertex3f(5, 0, 0);
  glEnd();
}
