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
public:
  typedef std::shared_ptr<Game> Ptr;
private:
  typedef std::map<unsigned char, std::function<void(int x, int y)>> KeyboardMap;

public:
  int start(int argc, char **argv);
  void draw();
  void keyboard(unsigned char key, int x, int y);

private:
  KeyboardMap keyboardMap;

  void initDrawCallback();
  void initKeyboardCallback();
  void initKeyboardMap();
};

extern Game::Ptr g_game;

// Extern C
extern "C" {
    static void drawCallback();
    static void keyboardCallback(unsigned char key, int x, int y);
}