#include <iostream>
#include <stdexcept>

#include "Game.hpp"

int main (int argc, char* argv[]) {
  try {
    Game game;
  } catch(const std::exception& ex) {
    std::cerr << "Runtime Error: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
