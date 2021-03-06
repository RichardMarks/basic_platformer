#ifndef GAME_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1920 / 2
#define SCREEN_HEIGHT 1080 / 2
#define WINDOW_TITLE "Basic Platformer"

class Game {
  struct Input {
    bool up;
    bool down;
    bool left;
    bool right;
    bool jump;

    int mouseX;
    int mouseY;
    bool mouseDown;
  };

  public:
    Game();
    ~Game();
    void load();
    void unload();
    void create();
    void destroy();
    void update(float deltaTime);
    void render();

    SDL_Window* mainWindowPtr;
    SDL_Renderer* mainRendererPtr;
    Input input;
    float timeScale;
    bool isRunning;
    bool isPaused;
};

#endif // !GAME_H
