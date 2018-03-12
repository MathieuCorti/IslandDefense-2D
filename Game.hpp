//
//  Game.hpp 
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#pragma once

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <iostream>
#include <map>

class Game {
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

extern Game *g_game;

// Extern C
static void drawCallback();

static void keyboardCallback(unsigned char key, int x, int y);