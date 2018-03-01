#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void destroy_game() {
   if (!currentGamePtr) {
    fprintf(stderr, "Error occurred in destroy_game()\nUnable to destroy game because: currentGamePtr is NULL!\n");
    return;
  }

  /* do your game cleanup here */

  currentGamePtr = NULL;

#ifndef PRODUCTION
  printf("executing destroy_game() -> currentGamePtr de-initialized.\n");
#endif
}
