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

  void draw() const;

  void keyboard(unsigned char key, int x, int y) const;

private:
  KeyboardMap _keyboardMap;
  EntityList _entities;

  void initDrawCallback() const;

  void initKeyboardCallback() const;

  void initKeyboardMap();

  void initGlut();

  void initEntities();

  static void displayTimer(int);

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