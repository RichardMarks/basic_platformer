#include "Platformer.hpp"

Vector2f Platformer::Physics::gravity(0.0f, 9.8f);
Vector2f Platformer::Physics::velocityLimit(22.0f, 6.0f);

Platformer::Platformer(Game const& gameRef)
  : game(gameRef) {

}

Platformer::~Platformer() {

}

void Platformer::load() {

}

void Platformer::unload() {

}

void Platformer::create() {
  player.size = Vector2u(32, 32);
  player.origin = Vector2f(player.size.x * 0.5f, player.size.y * 0.5f);
  player.position = Vector2f(SCREEN_WIDTH / 2, 0);
  player.velocity = Vector2f(0, 0);

  // ground.size = Vector2u(SCREEN_WIDTH, 16);
  // ground.position = Vector2f(0, SCREEN_HEIGHT - ground.size.y);
}

void Platformer::destroy() {

}

void Platformer::update(float deltaTime) {
  Game::Input const& input = game.input;

  // apply gravity to Y axis velocity
  player.velocity.y += Platformer::Physics::gravity.y;

  // keep velocity from getting out of hand
  player.velocity.y = clamp<float>(
    player.velocity.y,
    -Platformer::Physics::velocityLimit.y,
    Platformer::Physics::velocityLimit.y
  );

  // move player by velocity scaled by deltaTime for frame-rate independence
  player.position.y += player.velocity.y * deltaTime;
}

void Platformer::render() {
  SDL_Renderer* renderer = game.mainRendererPtr;

  SDL_Rect rect;

  int px = static_cast<int>(player.position.x);
  int py = static_cast<int>(player.position.y);

  // Y axis drawn at player's X coordinate
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawLine(renderer, px, 0, px, SCREEN_HEIGHT);

  // X axis drawn at player's Y coordinate
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderDrawLine(renderer, 0, py, SCREEN_WIDTH, py);

  // draw the player subtracting the origin so the origin is aligned with the axes
  rect.x = static_cast<int>(player.position.x - player.origin.x);
  rect.y = static_cast<int>(player.position.y - player.origin.y);
  rect.w = player.size.x;
  rect.h = player.size.y;

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &rect);
}
