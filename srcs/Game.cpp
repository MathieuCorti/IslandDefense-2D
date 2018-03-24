//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <vector>
#include "includes/Game.hpp"
#include "includes/Boat.hpp"
#include "helpers/Axes.hpp"
#include "includes/Projectile.hpp"
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
  glutIdleFunc(displayTimer);
  glutMainLoop();
  return EXIT_SUCCESS;
}

void Game::displayTimer() {
  glutPostRedisplay();
  getInstance().updateTime();
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
      {'q', [](int, int) { exit(EXIT_SUCCESS); }},
      {27,  [](int, int) { exit(EXIT_SUCCESS); }},
      {'a', [this](int, int) { move("left_boat", LEFT); }},
      {'d', [this](int, int) { move("left_boat", RIGHT); }},
      {'w', [this](int, int) { move("left_boat", UP); }},
      {'s', [this](int, int) { move("left_boat", DOWN); }},
      {'p', [this](int, int) { std::dynamic_pointer_cast<Cannon>(_entities["cannon"])->speed(0.1f); }},
      {'o', [this](int, int) { std::dynamic_pointer_cast<Cannon>(_entities["cannon"])->speed(-0.1f); }},
      {'i', [this](int, int) { std::dynamic_pointer_cast<Cannon>(_entities["cannon"])->rotation(0.1f); }},
      {'u', [this](int, int) { std::dynamic_pointer_cast<Cannon>(_entities["cannon"])->rotation(-0.1f); }}
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
  _entities.insert(std::make_pair("left_boat", std::make_shared<Boat>()));
  _entities.insert(std::make_pair("stats", std::make_shared<Stats>()));
//  _entities.insert(std::make_pair("axes", std::make_shared<Axes>()));
//  _entities.insert(std::make_pair("cannon", std::make_shared<Cannon>()));
}

float Game::getTime() const {
  return _time;
}

float Game::getLastTime() const {
  return _lastTime;
}

float Game::getDeltaTime() const {
  return _deltaTime;
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

float Game::getLastFrameRateT() const {
  return _lastFrameRateT;
}

float Game::getFrameRateInterval() const {
  return _frameRateInterval;
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