//
//  Game.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#if __APPLE__
#   include <OpenGL/OpenGL.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include "../helpers/Displayable.hpp"

class Game {

// TYPEDEFS
private:
  typedef std::map<unsigned char, std::function<void(int x, int y)>> KeyboardMap;
  typedef std::vector<std::shared_ptr<Displayable>> EntityList;

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