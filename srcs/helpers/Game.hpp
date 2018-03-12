//
//  Game.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/OpenGL.h>
#   include <OpenGL/OpenGL.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif
#include <cstdio>
#include <iostream>
#include <map>
#include <memory>

class Game {

// TYPEDEFS
private:
  typedef std::map<unsigned char, std::function<void(int x, int y)>> KeyboardMap;

public:
  static Game& getInstance() {
    static Game instance;
    return instance;
  }

  int start(int argc, char **argv) const;
  void draw() const;
  void keyboard(unsigned char key, int x, int y) const;

private:
  KeyboardMap keyboardMap;

  void initDrawCallback();
  void initKeyboardCallback();
  void initKeyboardMap();
  void initCamera();
};

  // Singleton
  Game()  = default;
  ~Game() = default;
  Game(const Game&)            = delete;
  Game& operator=(const Game&) = delete;
};

// Extern C
extern "C" {
  static void drawCallback();
  static void keyboardCallback(unsigned char key, int x, int y);
}