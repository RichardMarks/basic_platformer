#include <stdio.h>
#include <stdlib.h>
#include "game.h"

Game* currentGamePtr = NULL;
SDL_Window* mainWindowPtr = NULL;
SDL_Renderer* mainRendererPtr = NULL;

int init_game(Game* gamePtr, int cmdLineCount, char** cmdLine) {
  if (!gamePtr) {
    fprintf(stderr, "Error occurred in init_game()\nUnable to initialize game because: gamePtr is NULL!\n");
    return -1;
  }

  gamePtr->cmdLineCount = cmdLineCount;
  gamePtr->cmdLine = cmdLine;
  gamePtr->gameState = 1;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    SDL_Log("Error occurred in init_game()\nUnable to initialize SDL2: %s", SDL_GetError());
    return -1;
  }

  mainWindowPtr = SDL_CreateWindow(
    "My Project",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    480,
    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
  );

  if (!mainWindowPtr) {
    SDL_Log("Error occurred in init_game()\nUnable to create the main window: %s", SDL_GetError());
    return -1;
  }

  mainRendererPtr = SDL_CreateRenderer(
    mainWindowPtr,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE
  );

  if (!mainRendererPtr) {
    SDL_Log("Error occurred in init_game()\nUnable to create the main renderer: %s", SDL_GetError());
    return -1;
  }

  SDL_RenderSetLogicalSize(mainRendererPtr, 640, 480);
  SDL_MaximizeWindow(mainWindowPtr);

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
