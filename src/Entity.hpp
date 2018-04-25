#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>

#include "Vector2.hpp"

struct Hitbox {
  Hitbox() {}
  Hitbox(Vector2f l_position, Vector2u l_size, bool l_disabled)
    : position(l_position),
      size(l_size),
      disabled(l_disabled) {}
  Vector2f position;
  Vector2u size;
  bool disabled;
};

// these make defining hitboxes more intuitive
#define HITBOX_ENABLED false // hitbox.disabled = false
#define HITBOX_DISABLED true // hitbox.disabled = true

using HitboxList = std::map<std::string, Hitbox>;

struct Entity {
  Vector2u size;
  Vector2f origin;
  Vector2f position;
  Vector2f velocity;
  bool active;
  HitboxList hitboxes;
};

#endif // !ENTITY_H
