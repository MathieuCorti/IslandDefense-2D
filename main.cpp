//
//  main.cpp
//  IslandDefense
//
//  Created by Mathieu Corti on 3/12/18.
//

#include <cstdlib>

#include "srcs/helpers/Game.hpp"

Game::Ptr g_game;

int main(int argc, char **argv) {
  g_game =  std::make_shared<Game>();
  g_game->start(argc, argv);
  return EXIT_SUCCESS;
}