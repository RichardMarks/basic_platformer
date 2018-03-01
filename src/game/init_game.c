#include <stdio.h>
#include <stdlib.h>
#include "game.h"

Game* currentGamePtr = NULL;

int init_game(Game* gamePtr, int cmdLineCount, char** cmdLine) {
  if (!gamePtr) {
    fprintf(stderr, "Error occurred in init_game()\nUnable to initialize game because: gamePtr is NULL!\n");
    return -1;
  }

  gamePtr->cmdLineCount = cmdLineCount;
  gamePtr->cmdLine = cmdLine;
  gamePtr->gameState = 0;

  /* do your initialization here */

  currentGamePtr = gamePtr;

#ifndef PRODUCTION
  printf("executing init_game() -> currentGamePtr initialized.\n");
  printf("Argument Count: %d\n", cmdLineCount);
  printf("Arguments:\n");
  int i = 0;
  while (i < cmdLineCount) {
    printf("  [%2d] = %s\n", i, cmdLine[i]);
    i += 1;
  }
#endif

  return 0;
}
