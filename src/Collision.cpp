#include <algorithm>

#include "Collision.hpp"

Collision::Info Collision::entityVsEntity(Entity& a, Entity& b) {
  // test all hitboxes of "a" against all hitboxes of "b"
  Collision::Info result;
  result.hit = false;

  for (auto ita = a.hitboxes.begin(); ita != a.hitboxes.end(); ++ita) {
    auto& aBox = ita->second;

    auto aLeft = static_cast<int>((a.position.x - a.origin.x) + aBox.position.x);
    auto aTop = static_cast<int>((a.position.y - a.origin.y) + aBox.position.y);
    auto aRight = static_cast<int>(aLeft + aBox.size.x);
    auto aBottom = static_cast<int>(aTop + aBox.size.y);

    for (auto itb = b.hitboxes.begin(); itb != b.hitboxes.end(); ++itb) {
      auto& bBox = itb->second;

      auto bLeft = static_cast<int>((b.position.x - b.origin.x) + bBox.position.x);
      auto bTop = static_cast<int>((b.position.y - b.origin.y) + bBox.position.y);
      auto bRight = static_cast<int>(bLeft + bBox.size.x);
      auto bBottom = static_cast<int>(bTop + bBox.size.y);

      auto x1 = std::max(aLeft, bLeft);
      auto x2 = std::min(aRight, bRight);
      if (x2 > x1) {
        auto y1 = std::max(aTop, bTop);
        auto y2 = std::min(aBottom, bBottom);
        if (y2 > y1) {
          result.hit = true;
          result.left = x1;
          result.top = y1;
          result.right = x2;
          result.bottom = y2;
          return result;
        }
      }
    }
  }

  return result;
}

Collision::Info Collision::entityVsHitbox(Entity& a, Entity& b, std::string hitboxName) {
  // test all hitboxes of "a" against entity "b" 's hitbox "hitboxName"
  Collision::Info result;
  result.hit = false;

  auto itb = b.hitboxes.find(hitboxName);

  if (itb != b.hitboxes.end()) {
    auto& bBox = itb->second;

    auto bLeft = static_cast<int>((b.position.x - b.origin.x) + bBox.position.x);
    auto bTop = static_cast<int>((b.position.y - b.origin.y) + bBox.position.y);
    auto bRight = static_cast<int>(bLeft + bBox.size.x);
    auto bBottom = static_cast<int>(bTop + bBox.size.y);

    for (auto ita = a.hitboxes.begin(); ita != a.hitboxes.end(); ++ita) {
      auto& aBox = ita->second;

      auto aLeft = static_cast<int>((a.position.x - a.origin.x) + aBox.position.x);
      auto aTop = static_cast<int>((a.position.y - a.origin.y) + aBox.position.y);
      auto aRight = static_cast<int>(aLeft + aBox.size.x);
      auto aBottom = static_cast<int>(aTop + aBox.size.y);

      auto x1 = std::max(aLeft, bLeft);
      auto x2 = std::min(aRight, bRight);
      if (x2 > x1) {
        auto y1 = std::max(aTop, bTop);
        auto y2 = std::min(aBottom, bBottom);
        if (y2 > y1) {
          result.hit = true;
          result.left = x1;
          result.top = y1;
          result.right = x2;
          result.bottom = y2;
          return result;
        }
      }
    }
  }

  return result;
}
