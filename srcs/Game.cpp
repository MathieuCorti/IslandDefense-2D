//
//  Game.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <vector>
#include "includes/Game.hpp"
#include "includes/Island.hpp"
#include "includes/Stats.hpp"
#include "includes/UI.hpp"
#include "includes/Config.hpp"

// PUBLIC

int Game::start(int argc, char **argv) {
  // Init
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
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

  // Update entities
  for (auto it = _entities.cbegin(); it != _entities.cend();) {
    if (it->second->update()) {
      std::cout << "dafuu : " << it->first << std::endl;
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

  for (const auto &entity : _entities) {
//    std::cout << "drawing : " << entity.first << std::endl;
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

void Game::initKeyboardMap() {
  _keyboardMap = {
      {27,  [](int, int) { exit(EXIT_SUCCESS); }},

      // LEFT BOAT COMMANDS
      {'a', [this](int, int) { move(LEFT_BOAT, LEFT); }},
      {'d', [this](int, int) { move(LEFT_BOAT, RIGHT); }},
      {'e', [this](int, int) { fire<Boat>(LEFT_BOAT); }},
      {'z', [this](int, int) { defend<Boat>(LEFT_BOAT); }},
      {'q', [this](int, int) { changeCannonPower<Boat>(LEFT_BOAT, INCREASE); }},
      {'Q', [this](int, int) { changeCannonPower<Boat>(LEFT_BOAT, DECREASE); }},
      {'s', [this](int, int) { changeCannonDirection<Boat>(LEFT_BOAT, INCREASE); }},
      {'S', [this](int, int) { changeCannonDirection<Boat>(LEFT_BOAT, DECREASE); }},

      // RIGHT BOAT COMMANDS
      {'j', [this](int, int) { move(RIGHT_BOAT, LEFT); }},
      {'l', [this](int, int) { move(RIGHT_BOAT, RIGHT); }},
      {'i', [this](int, int) { fire<Boat>(RIGHT_BOAT); }},
      {'m', [this](int, int) { defend<Boat>(RIGHT_BOAT); }},
      {'o', [this](int, int) { changeCannonPower<Boat>(RIGHT_BOAT, INCREASE); }},
      {'O', [this](int, int) { changeCannonPower<Boat>(RIGHT_BOAT, DECREASE); }},
      {'k', [this](int, int) { changeCannonDirection<Boat>(RIGHT_BOAT, INCREASE); }},
      {'K', [this](int, int) { changeCannonDirection<Boat>(RIGHT_BOAT, DECREASE); }},

      //ISLAND COMMANDS
      {'g', [this](int, int) { fire<Island>(ISLAND); }},
      {'b', [this](int, int) { defend<Island>(ISLAND); }},
      {'f', [this](int, int) { changeCannonPower<Island>(ISLAND, INCREASE); }},
      {'F', [this](int, int) { changeCannonPower<Island>(ISLAND, DECREASE); }},
      {'h', [this](int, int) { changeCannonDirection<Island>(ISLAND, INCREASE); }},
      {'H', [this](int, int) { changeCannonDirection<Island>(ISLAND, DECREASE); }},

      // WAVES COMMANDS
      {'n', [this](int, int) { toggleNormals(WAVES); }},
      {'t', [this](int, int) { toggleTangeants(WAVES); }},
      {'w', [this](int, int) { toggleWireframe(WAVES); }},
      {'!', [this](int, int) { toggleAnimate(WAVES); }},
      {'+', [this](int, int) { doubleVertices(WAVES); }},
      {'-', [this](int, int) { halveSegments(WAVES); }},
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
  Island::Ptr island = std::make_shared<Island>(ISLAND_COLOR);
  _entities.insert(std::make_pair(ISLAND, island));
  _entities.insert(std::make_pair(WAVES, std::make_shared<Waves>()));
  Boat::Ptr leftBoat = std::make_shared<Boat>(-BOAT_START_X, CANNON_RIGHT, CANNON_ROTATION_RIGHT, LEFT_BOAT_COLOR, STANDARD);
  Boat::Ptr rightBoat = std::make_shared<Boat>(BOAT_START_X, CANNON_LEFT, CANNON_ROTATION_LEFT, RIGHT_BOAT_COLOR, INVERTED);
  _entities.insert(std::make_pair(PELLETS, std::make_shared<Entities<Pellet::Ptr>>()));
  _entities.insert(std::make_pair(LEFT_BOAT, leftBoat));
  _entities.insert(std::make_pair(RIGHT_BOAT, rightBoat));
  _entities.insert(std::make_pair(ISLAND, island));
  _entities.insert(std::make_pair(WAVES, std::make_shared<Waves>()));
  _entities.insert(std::make_pair(STATS, std::make_shared<Stats>()));
  UI::Entities entities = {
      std::make_pair(std::dynamic_pointer_cast<Alive>(island), ISLAND_COLOR),
      std::make_pair(std::dynamic_pointer_cast<Alive>(rightBoat), RIGHT_BOAT_COLOR),
      std::make_pair(std::dynamic_pointer_cast<Alive>(leftBoat), LEFT_BOAT_COLOR)
  };
  _entities.insert(std::make_pair(GAME_UI, std::make_shared<UI>(entities)));
  _entities.insert(std::make_pair(AXES, std::make_shared<Axes>()));
  _entities.insert(std::make_pair(LEFT_BOAT_PROJECTILES, std::make_shared<Entities<Projectile::Ptr>>()));
  _entities.insert(std::make_pair(RIGHT_BOAT_PROJECTILES, std::make_shared<Entities<Projectile::Ptr>>()));
  _entities.insert(std::make_pair(ISLAND_PROJECTILES, std::make_shared<Entities<Projectile::Ptr>>()));
}

const float Game::getTime() const {
  return _time / SPEED;
}

const float &Game::getDeltaTime() const {
  return _deltaTime;
}

void Game::updateTime() {
  _time = glutGet(GLUT_ELAPSED_TIME) / MILLI;

  if (_lastTime == 0.0) {
    _lastTime = _time;
    return;
  }

  _lastTime = _time;


  _deltaTime = _time - _lastFrameRateT;
  if (_deltaTime > _frameRateInterval) {
    _frameRate = _frames / _deltaTime;
    _lastFrameRateT = _time;
    _frames = 0;
  }
}

const float &Game::getFrameRate() const {
  return _frameRate;
}

const Game::EntityList &Game::getEntities() const {
  return _entities;
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