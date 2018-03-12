//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <vector>
#include "helpers/Game.hpp"
#include "helpers/Island.hpp"

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
  initCamera();
  glutMainLoop();
  return EXIT_SUCCESS;
}

void Game::draw() const {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  std::vector<Displayable *> entities;
  entities.push_back(new Island());
  for (const Displayable *d : entities) {
    d->draw();
    for (GLenum err = 0; (err = glGetError());) {
      printf("%s\n", gluErrorString(err));
    }
  }

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

void Game::initCamera() {
  if (g_game.get() == this) {
    glMatrixMode(GL_PROJECTION);
    glOrtho(-10.0, 10.0, -10.0, 10.0, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
  }
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