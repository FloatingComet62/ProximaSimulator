#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "medium.hpp"
#include "object.hpp"

/// # World
/// @brief The world environment
class World {
 private:
  std::vector<Object> objects;
  std::vector<Medium> mediums;

 public:
  float gravity;

  /// @brief Initialize the world
  World(float gravity = 0);

  /// @brief Add an object to the world
  /// @param object Object to add
  void addObject(Object object);

  /// @brief Add a medium to the world
  /// @param medium Medium to add
  void addMedium(Medium medium);
};

#endif