#ifndef VECTOR2_H
#define VECTOR2_H

template <typename T>
class Vector2 {
  public:
    Vector2();
    Vector2(T x, T y);

    template <typename U>
    explicit Vector2(const Vector2<U>& vector);

    T x;
    T y;
};

#include "Vector2.inl"

using Vector2u = Vector2<unsigned>;
using Vector2f = Vector2<float>;

#endif // !VECTOR2_H
