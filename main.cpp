//
//  main.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <stdlib.h>

#include "Game.hpp"

Game *g_game;

int main(int argc, char **argv) {
  g_game = new Game();
  g_game->start(argc, argv);
  return EXIT_SUCCESS;
}