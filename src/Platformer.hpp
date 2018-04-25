#ifndef PLATFORMER_H
#define PLATFORMER_H

#include "Game.hpp"

#include "Entity.hpp"

class Platformer {
  public:
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

#endif // !PLATFORMER_H
