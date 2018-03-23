//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <vector>
#include "includes/Game.hpp"
#include "includes/Boat.hpp"
#include "includes/Waves.hpp"
#include "helpers/Axes.hpp"
#include "includes/Island.hpp"

#define REFRESH_RATE 16
#define MOVE()

// PUBLIC

int Game::start(int argc, char **argv) {
  // Init
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Island Defense 2D");

  // Start
  initDrawCallback();
  initKeyboardCallback();
  initKeyboardMap();
  initGlut();
  initEntities();
  glutTimerFunc(REFRESH_RATE, displayTimer, 0);
  glutMainLoop();
  return EXIT_SUCCESS;
}

void Game::displayTimer(int) {
  glutPostRedisplay();
  glutTimerFunc(REFRESH_RATE, displayTimer, 0);
}

void Game::draw() const {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (const auto entity : _entities) {
    entity.second->draw();
    for (GLenum err = 0; (err = glGetError());) {
      printf("%s\n", gluErrorString(err));
    }
  }

  glutSwapBuffers();
}

void Game::keyboard(unsigned char key, int x, int y) const {
  auto iter = _keyboardMap.find(key);
  if (iter != _keyboardMap.end()) {
    iter->second.operator()(x, y);
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
 */
void Game::initKeyboardMap() {
  _keyboardMap = {
      {'q'  , [](int, int) { exit(EXIT_SUCCESS); }},
      {27   , [](int, int) { exit(EXIT_SUCCESS); }},
      {'a'  , [this](int, int) { move("left_boat", LEFT);   }},
      {'d'  , [this](int, int) { move("left_boat", RIGHT);  }},
      {'w'  , [this](int, int) { move("left_boat", UP);     }},
      {'s'  , [this](int, int) { move("left_boat", DOWN);   }}

  };
}

void Game::initDrawCallback() const {
  glutDisplayFunc(drawCallback);
}

void Game::initKeyboardCallback() const {
  glutKeyboardFunc(keyboardCallback);
}

void Game::initGlut() {
  glMatrixMode(GL_PROJECTION);
  glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);
  glMatrixMode(GL_MODELVIEW);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::initEntities() {
  _entities.insert(std::make_pair( "island"    , std::make_shared<Island>() ));
  _entities.insert(std::make_pair( "waves"     , std::make_shared<Waves>()  ));
  _entities.insert(std::make_pair( "left_boat" , std::make_shared<Boat>()   ));
//  _entities.insert(std::make_pair( "axes"   , std::make_shared<Axes>()   ));
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