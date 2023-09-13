#ifndef MEDIUM_H
#define MEDIUM_H

#include "vectors.hpp"

/// # Medium
/// @brief The medium that will surround the objects in the world
class Medium {
 private:
  v2 top_left;
  v2 bottom_right;

 public:
  float viscosity;
};

#endif