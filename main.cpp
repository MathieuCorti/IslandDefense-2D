//
//  main.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <stdlib.h>

#include "srcs/Game.hpp"

int main(int argc, char **argv) {
  Game::getInstance().start(argc, argv);
  return EXIT_SUCCESS;
}