//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <vector>
#include "includes/Game.hpp"
#include "includes/Boat.hpp"
#include "includes/Island.hpp"
#include "includes/Waves.hpp"
#include "includes/Stats.hpp"

// PUBLIC

#define MILLI 1000.0f

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
  glutIdleFunc(idleFunc);
  glutMainLoop();
  return EXIT_SUCCESS;
}

void Game::idleFunc() {
  Game::getInstance().update();
  glutPostRedisplay();
}

void Game::update() {
  updateTime();
  for (auto it = _entities.cbegin(); it != _entities.cend();) {
    if (it->second->update()) {
      it = _entities.erase(it++);
    } else {
      ++it;
    }
  }
}

void Game::draw() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
//  gluLookAt(0.3, 0.3, 1, 0, 0, 0, 0, 1, 0);

  for (const auto &entity : _entities) {
    entity.second->draw();
    for (GLenum err = 0; (err = glGetError());) {
      printf("%s\n", gluErrorString(err));
    }
  }

  _frames++;

  glutSwapBuffers();
}

void Game::keyboard(unsigned char key, int x, int y) const {
  switch (glutGetModifiers()) {
    case GLUT_ACTIVE_SHIFT:
      key = static_cast<unsigned char>(toupper(key));
      break;
    default:
      break;
  }
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
 * r: Left boat defence
 * y: Right boat defence
 * g: Toggle wave animation on/off
 * +: Double wave tesselation
 * -: Halve wave tesselation
 */
void Game::initKeyboardMap() {
  _keyboardMap = {
      {27,  [](int, int) { exit(EXIT_SUCCESS); }},

      // LEFT BOAT COMMANDS
      {'a', [this](int, int) { move("left_boat", LEFT); }},
      {'d', [this](int, int) { move("left_boat", RIGHT); }},
      {'e', [this](int, int) { fire("left_boat"); }},
      {'q', [this](int, int) { changeCannonPower("left_boat", 0.1f); }},
      {'Q', [this](int, int) { changeCannonPower("left_boat", -0.1f); }},
      {'s', [this](int, int) { changeCannonDirection("left_boat", 0.1f); }},
      {'S', [this](int, int) { changeCannonDirection("left_boat", -0.1f); }},

      // RIGHT BOAT COMMANDS
      {'j', [this](int, int) { move("right_boat", LEFT); }},
      {'l', [this](int, int) { move("right_boat", RIGHT); }},
      {'i', [this](int, int) { fire("right_boat"); }},
      {'o', [this](int, int) { changeCannonPower("right_boat", 0.1f); }},
      {'O', [this](int, int) { changeCannonPower("right_boat", -0.1f); }},
      {'k', [this](int, int) { changeCannonDirection("right_boat", 0.1f); }},
      {'K', [this](int, int) { changeCannonDirection("right_boat", -0.1f); }},
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
  _entities.insert(std::make_pair("island", std::make_shared<Island>()));
  _entities.insert(std::make_pair("waves", std::make_shared<Waves>()));
  _entities.insert(std::make_pair("left_boat", std::make_shared<Boat>(-0.65, 0.04)));
  _entities.insert(std::make_pair("right_boat", std::make_shared<Boat>(0.65, -0.04)));
  _entities.insert(std::make_pair("stats", std::make_shared<Stats>()));
//  _entities.insert(std::make_pair("axes", std::make_shared<Axes>()));
}

float Game::getTime() const {
  return _time;
}

void Game::updateTime() {
  _time = glutGet(GLUT_ELAPSED_TIME) / MILLI;

  if (_lastTime == 0.0) {
    _lastTime = _time;
    return;
  }

  _deltaTime = _time - _lastTime;
  _lastTime = _time;

  _deltaTime = _time - _lastFrameRateT;
  if (_deltaTime > _frameRateInterval) {
    _frameRate = _frames / _deltaTime;
    _lastFrameRateT = _time;
    _frames = 0;
  }
}

float Game::getFrameRate() const {
  return _frameRate;
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