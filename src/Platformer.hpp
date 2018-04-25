#ifndef PLATFORMER_H
#define PLATFORMER_H

#include "Game.hpp"

#include "Entity.hpp"

class Platformer {
  public:
    struct Physics {
      static Vector2f gravity;
      static Vector2f velocityLimit;
    };
    Platformer(Game const& gameRef);
    ~Platformer();
    void load();
    void unload();
    void create();
    void destroy();
    void update(float deltaTime);
    void render();

    Game const& game;

    Entity player;
};

template <typename T>
T clamp(T value, T minimum, T maximum) {
  return value < minimum ? minimum : (value > maximum ? maximum : value);
}

#endif // !PLATFORMER_H
