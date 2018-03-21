//
//  Boat.cpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include "helpers/OpenGL.hpp"
#include "helpers/Glut.hpp"

#include "includes/Waves.hpp"
#include "includes/Boat.hpp"

void Boat::draw() const {

  for (auto shape: _shapes) {
    shape.draw();
  }

//  // Draw the hull
//  glBegin(GL_POLYGON);
//  glVertex2d(-0.05, Waves::computeHeight(0) -0.25);
//  glVertex2d(0.05,Waves::computeHeight(0) -0.25);
//  glVertex2d(0.1, Waves::computeHeight(0) + 0.25);
//  glVertex2d(-0.1, Waves::computeHeight(0) + 0.25);
//  glEnd();
//
//  // Draw the bridge
//  glBegin(GL_POLYGON);
//  glVertex2d(-0.25, Waves::computeHeight(0) + 0.25);
//  glVertex2d(0.25, Waves::computeHeight(0) + 0.25);
//  glVertex2d(0.25, Waves::computeHeight(0) + 0.65);
//  glVertex2d(-0.25, Waves::computeHeight(0) + 0.65);
//  glEnd();
//
//  // Draw the cannon

}