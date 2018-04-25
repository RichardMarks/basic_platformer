#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.hpp"

struct Entity {
  Vector2u size;
  Vector2f origin;
  Vector2f position;
  Vector2f velocity;
  bool active;
};

#endif // !ENTITY_H
