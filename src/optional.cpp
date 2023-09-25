#include "optional.hpp"

template<class T>
Optional<T>::Optional() {
  this->has_value = false;
  this->data = nullptr;
}

template<class T>
Optional<T>::Optional(T data) {
  this->has_value = true;
  this->data = data;
}

template<class T>
bool Optional<T>::hasValue() {
  return this->has_value;
}

template<class T>
T Optional<T>::getData() {
  return this->data;
}
