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

  SDL_Event event;
  while (gamePtr->gameState) {
    SDL_SetRenderDrawColor(mainRendererPtr, 0x30, 0x60, 0x90, 0xFF);
    SDL_RenderClear(mainRendererPtr);
    /* render your stuff here */
    SDL_RenderPresent(mainRendererPtr);
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        gamePtr->gameState = 0;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          gamePtr->gameState = 0;
        }
      }
    }
  }

  return 0;
}
