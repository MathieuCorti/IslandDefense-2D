//
//  Game.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include "../helpers/Glut.hpp"
#include "../helpers/OpenGL.hpp"

#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>

#include "../helpers/Displayable.hpp"
#include "../helpers/Movable.hpp"

class Game {

// TYPEDEFS
private:
  typedef std::map<unsigned char, std::function<void(int x, int y)>> KeyboardMap;
  typedef std::map<std::string, Displayable::Ptr> EntityList;

public:
  static Game &getInstance() {
    static Game instance;
    return instance;
  }

  int start(int argc, char **argv);

  void draw();

  void keyboard(unsigned char key, int x, int y) const;

  float getTime() const;

  float getFrameRate() const;

private:
  KeyboardMap _keyboardMap;
  EntityList _entities;
  float _time, _lastTime, _deltaTime = 0.0;
  float _lastFrameRateT, _frameRateInterval, _frameRate, _frames;

  void initDrawCallback() const;

  void initKeyboardCallback() const;

  void initKeyboardMap();

  void initGlut();

  void initEntities();

  void update();

  void updateTime();

  static void idleFunc();

  // Helpers

  void move(std::string entityName, Direction direction) {
    std::dynamic_pointer_cast<Movable>(_entities[entityName])->move(direction);
  }

  // Singleton
  Game() = default;

  ~Game() = default;

  Game(const Game &) = delete;

  Game &operator=(const Game &) = delete;
};

// Extern C
extern "C" {
static void drawCallback();
static void keyboardCallback(unsigned char key, int x, int y);
}