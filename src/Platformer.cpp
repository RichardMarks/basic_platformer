#include "Platformer.hpp"
#include "Collision.hpp"

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
  player.position = Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
  player.velocity = Vector2f(0, 0);

  // hitboxes are positioned relative to the entity's upper-left corner (e.pos - e.origin)
  player.hitboxes["foot"] = Hitbox(
    Vector2f(6, 24),
    Vector2u(20, 8),
    HITBOX_ENABLED
  );

  ground.size = Vector2u(SCREEN_WIDTH, 16);
  ground.position = Vector2f(0, SCREEN_HEIGHT - ground.size.y);

  ground.hitboxes["main"] = Hitbox(
    Vector2f(0, 0),
    ground.size,
    HITBOX_ENABLED
  );
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

  if (Collision::entityVsHitbox(player, ground, "main").hit) {
    player.position.y -= player.velocity.y * deltaTime;
  }

  // if (player.position.y > SCREEN_HEIGHT) {
  //   player.position.y = 0;
  // }
}

void Platformer::render() {
  SDL_Renderer* renderer = game.mainRendererPtr;

  int px = static_cast<int>(player.position.x);
  int py = static_cast<int>(player.position.y);

  // Y axis drawn at player's X coordinate
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
  SDL_RenderDrawLine(renderer, px, 0, px, SCREEN_HEIGHT);

  // X axis drawn at player's Y coordinate
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderDrawLine(renderer, 0, py, SCREEN_WIDTH, py);

  renderEntity(ground, 0x68, 0x3F, 0x22, 0xFF);
  renderEntity(player, 0xFF, 0xFF, 0xFF, 0xFF);

  // render the collision hitboxes
  renderEntityDebug(player);
  renderEntityDebug(ground);
}

void Platformer::renderEntity(Entity& entity, unsigned red, unsigned green, unsigned blue, unsigned alpha) {
  SDL_Renderer* renderer = game.mainRendererPtr;

  SDL_Rect rect;

  // draw the entity subtracting the origin so the origin is aligned with the axes
  rect.x = static_cast<int>(entity.position.x - entity.origin.x);
  rect.y = static_cast<int>(entity.position.y - entity.origin.y);
  rect.w = entity.size.x;
  rect.h = entity.size.y;

  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
  SDL_RenderFillRect(renderer, &rect);
}

void Platformer::renderEntityDebug(Entity& entity) {
  // no hitboxes - abort mission
  if (!entity.hitboxes.size()) {
    return;
  }

  SDL_Renderer* renderer = game.mainRendererPtr;

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  SDL_Rect rect;

  int ex = static_cast<int>(entity.position.x - entity.origin.x);
  int ey = static_cast<int>(entity.position.y - entity.origin.y);

  for (auto it = entity.hitboxes.begin(); it != entity.hitboxes.end(); ++it) {
    auto& box = it->second;
    if (box.disabled) {
      SDL_SetRenderDrawColor(renderer, 0x50, 0x50, 0x50, 192);
    } else {
      SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 128);
    }

    rect.x = ex + static_cast<int>(box.position.x);
    rect.y = ey + static_cast<int>(box.position.y);
    rect.w = box.size.x;
    rect.h = box.size.y;
    SDL_RenderFillRect(renderer, &rect);
  }

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}
