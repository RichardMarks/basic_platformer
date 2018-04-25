#ifndef COLLISION_H
#define COLLISION_H

#include "Entity.hpp"

class Collision {
  public:
    struct Info {
      int left;
      int top;
      int right;
      int bottom;
      bool hit;
    };

  static Collision::Info entityVsEntity(Entity& a, Entity& b);

  static Collision::Info entityVsHitbox(Entity& a, Entity& b, std::string hitboxName);
};

#endif // !COLLISION_H
