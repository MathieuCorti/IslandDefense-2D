//
// Created by wilmot_g on 23/03/18.
//

#include "helpers/Glut.hpp"

#include <cstdio>
#include "includes/Stats.hpp"
#include "includes/Game.hpp"

void Stats::draw() const
{
  char buffer[30];
  char *bufp;
  int w, h;

  glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  /* Set up orthographic coordinate system to match the
     window, i.e. (0,0)-(w,h) */
  w = glutGet(GLUT_WINDOW_WIDTH);
  h = glutGet(GLUT_WINDOW_HEIGHT);
  glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  auto &game = Game::getInstance();

  /* Frame rate */
  glColor3f(1.0, 1.0, 0.0);
  glRasterPos2i(10, h - 20);
  snprintf(buffer, sizeof buffer, "fps        : %3.0f", game.getFrameRate());
  for (bufp = buffer; *bufp; bufp++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);
  }

  /* Time per frame */
  glColor3f(1.0, 1.0, 0.0);
  glRasterPos2i(10, h - 40);
  snprintf(buffer, sizeof buffer, "frame time : %3.0fms", 1.0 / game.getFrameRate() * 1000.0);
  for (bufp = buffer; *bufp; bufp++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *bufp);
  }

  /* Pop modelview */
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);

  /* Pop projection */
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  /* Pop attributes */
  glPopAttrib();
}
