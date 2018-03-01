#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int run_game(Game* gamePtr) {
  if (!gamePtr) {
    fprintf(stderr, "Error occurred in run_game()\nUnable to run game because: gamePtr is NULL!\n");
    return -1;
  }

#ifndef PRODUCTION
  printf("executing run_game()\n");
#endif

  return 0;
}
