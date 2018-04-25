template <typename T>
inline Vector2<T>::Vector2() : x(0), y(0) {

}

template <typename T>
inline Vector2<T>::Vector2(T l_x, T l_y) : x(l_x), y(l_y) {

}

template <typename T>
template <typename U>
inline Vector2<T>::Vector2(const Vector2<U>& vector)
  : x(static_cast<T>(vector.x)),
    y(static_cast<T>(vector.y)) {
}
