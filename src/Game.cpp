#include "Platformer.hpp"
#include "Game.hpp"

Game::Game()
  : mainWindowPtr(nullptr),
    mainRendererPtr(nullptr) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::stringstream msg;
    msg << "Error occurred in init_game()\nUnable to initialize SDL2: " << SDL_GetError() << std::endl;
    throw std::runtime_error(msg.str());
  }

  mainWindowPtr = SDL_CreateWindow(
    WINDOW_TITLE,
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
  );

  if (!mainWindowPtr) {
    std::stringstream msg;
    msg << "Error occurred in init_game()\nUnable to create the main window: " << SDL_GetError() << std::endl;
    throw std::runtime_error(msg.str());
  }

  mainRendererPtr = SDL_CreateRenderer(
    mainWindowPtr,
    -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE
  );

  if (!mainRendererPtr) {
    std::stringstream msg;
    msg << "Error occurred in init_game()\nUnable to create the main renderer:" << SDL_GetError() << std::endl;
    throw std::runtime_error(msg.str());
  }

  SDL_RenderSetLogicalSize(mainRendererPtr, SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_MaximizeWindow(mainWindowPtr);

  platformer = new Platformer(*this);

  load();
  create();

  isRunning = true;
  isPaused = false;

  input.up = false;
  input.down = false;
  input.left = false;
  input.right = false;
  input.jump = false;
  input.mouseX = 0;
  input.mouseY = 0;
  input.mouseDown = false;

  SDL_Event sdlEvent;

  float lastTime = static_cast<float>(SDL_GetTicks() * 0.001f);
  float newTime = 0;
  float deltaTime = 0.0f;

  timeScale = 1.0f;

  while (isRunning) {
    newTime = static_cast<float>(SDL_GetTicks() * 0.001f);
    if (newTime - lastTime < 1) {
      deltaTime = (newTime - lastTime) * timeScale;
      update(60 * deltaTime);
    }
    lastTime = newTime;

    render();

    while (SDL_PollEvent(&sdlEvent)) {
      switch (sdlEvent.type) {
        case SDL_QUIT: {
          isRunning = false;
        } break;

        case SDL_KEYDOWN: {
          switch (sdlEvent.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE: { isRunning = false; } break;
            case SDL_SCANCODE_W: { input.up = true; } break;
            case SDL_SCANCODE_S: { input.down = true; } break;
            case SDL_SCANCODE_A: { input.left = true; } break;
            case SDL_SCANCODE_D: { input.right = true; } break;

            case SDL_SCANCODE_UP: { input.up = true; } break;
            case SDL_SCANCODE_DOWN: { input.down = true; } break;
            case SDL_SCANCODE_LEFT: { input.left = true; } break;
            case SDL_SCANCODE_RIGHT: { input.right = true; } break;

            case SDL_SCANCODE_SPACE: { input.jump = true; } break;
            default: break;
          }
        } break;

        case SDL_KEYUP: {
          switch (sdlEvent.key.keysym.scancode) {
            case SDL_SCANCODE_W: { input.up = false; } break;
            case SDL_SCANCODE_S: { input.down = false; } break;
            case SDL_SCANCODE_A: { input.left = false; } break;
            case SDL_SCANCODE_D: { input.right = false; } break;

            case SDL_SCANCODE_UP: { input.up = false; } break;
            case SDL_SCANCODE_DOWN: { input.down = false; } break;
            case SDL_SCANCODE_LEFT: { input.left = false; } break;
            case SDL_SCANCODE_RIGHT: { input.right = false; } break;

            case SDL_SCANCODE_SPACE: { input.jump = false; } break;
            default: break;
          }
        } break;

        case SDL_MOUSEMOTION: {
          input.mouseX = sdlEvent.motion.x;
          input.mouseY = sdlEvent.motion.y;
        } break;

        case SDL_MOUSEBUTTONDOWN: {
          input.mouseDown = true;
          input.mouseX = sdlEvent.button.x;
          input.mouseY = sdlEvent.button.y;
        } break;

        case SDL_MOUSEBUTTONUP: {
          input.mouseDown = false;
          input.mouseX = sdlEvent.button.x;
          input.mouseY = sdlEvent.button.y;
        } break;

        default: break;
      }
    }
  }
}

Game::~Game() {
  destroy();
  unload();
  delete platformer;
  platformer = nullptr;
  SDL_DestroyRenderer(mainRendererPtr);
  SDL_DestroyWindow(mainWindowPtr);
  SDL_Quit();
}

void Game::load() {
  // load resources
  platformer->load();
}

void Game::unload() {
  // free resources
  platformer->unload();
}

void Game::create() {
  // allocate objects
  platformer->create();
}

void Game::destroy() {
  // free objects
  platformer->destroy();
}

void Game::update(float deltaTime) {
  // update objects
  platformer->update(deltaTime);
}

void Game::render() {
  // SDL_SetRenderDrawColor(mainRendererPtr, 0x30, 0x60, 0x90, 0xFF);
  SDL_SetRenderDrawColor(mainRendererPtr, 0x10, 0x10, 0x10, 0xFF);
  SDL_RenderClear(mainRendererPtr);

  // draw objects
  platformer->render();

  SDL_RenderPresent(mainRendererPtr);
}
