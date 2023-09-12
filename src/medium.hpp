#ifndef MEDIUM_H
#define MEDIUM_H

#include "world.hpp"

/// # Medium
/// @brief The medium that will surround the objects in the world
class Medium {
 private:
  v2 top_left;
  v2 bottom_right;
  World& world;

 public:
  float viscosity;
};

#endif