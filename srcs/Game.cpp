//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include "Game.hpp"

// PUBLIC

int Game::start(int argc, char **argv) const {
  // Init
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Island Defense 2D");

  // Start
  initDrawCallback();
  initKeyboardCallback();
  initKeyboardMap();
  glutMainLoop();
  return EXIT_SUCCESS;
}

void Game::draw() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  // DRAW
  glutSwapBuffers();
}

void Game::keyboard(unsigned char key, int x, int y) const {
  for (auto const& keyboardEntree : keyboardMap) {
    if (keyboardEntree.first == key) {
      return keyboardEntree.second.operator()(x, y);
    }
  }
}

// PRIVATE

/**
 * F1: Toggle wireframe mode on/off
 * n: Toggle normal visualisation on/off
 * q: Left cannon rotate up
 * Q: Left cannon rotate down
 * a: Left boat move left
 * d: Left boat move right
 * o: Right cannon rotate up
 * O: Right cannon rotate down
 * l: Right boat move left: Right boat move right
 * e: Left boat fire
 * i: Right boat fire
 * r: Left boat defence
 * y: Right boat defence
 * g: Toggle wave animation on/off
 * +: Double wave tesselation
 * -: Halve wave tesselation
 * q/Esc: Quit the program
 */
void Game::initKeyboardMap() const {
  KeyboardMap keyboardMap = {
      { 'q' , [](int, int) { exit(EXIT_SUCCESS); }  },
      { 27  , [](int, int) { exit(EXIT_SUCCESS); }  }
  };
}

void Game::initDrawCallback() const {
  ::glutDisplayFunc(::drawCallback);
}

void Game::initKeyboardCallback() const {
  ::glutKeyboardFunc(::keyboardCallback);
}

// EXTERN C

extern "C" {
static void drawCallback() {
  Game::getInstance().draw();
}
static void keyboardCallback(unsigned char key, int x, int y) {
  Game::getInstance().keyboard(key, x, y);
}
}