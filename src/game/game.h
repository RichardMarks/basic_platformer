#ifndef GAME_H
#define GAME_H

/*
  a simple structure to hold game-related information
*/
typedef struct Game {
  /* number of arguments passed on the command line. (includes the program itself as the 0th element) */
  int cmdLineCount;

  /* actual array of arguments passed on the command line. program name is the 0th element */
  char** cmdLine;

  /* current game state */
  int gameState;
} Game;

/*
  global pointer to the game instance that has been init by init_game()
  destroy_game() will use this to clean up when the program's main() exits.
*/
extern Game* currentGamePtr;

extern int init_game(Game* gamePtr, int cmdLineCount, char** cmdLine);
extern int run_game(Game* gamePtr);
extern void destroy_game();

#endif
