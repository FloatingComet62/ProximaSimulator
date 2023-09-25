#ifndef WORLD
#define WORLD

#include <vector>

#include "medium.hpp"
#include "object.hpp"
#include "window.hpp"

/// # World
/// @brief The world environment
class World {
 private:
  Window* window;

 public:
  std::vector<Object*> objects;
  std::vector<Medium*> mediums;
  float gravity;

  /// @brief Initialize the world
  /// @param window Window to display the world
  /// @param gravity Gravity of the world
  World(Window* window, float gravity = 0);

  /// @brief Add an object to the world
  /// @param object Object to add
  void addObject(Object* object);

  /// @brief Add a medium to the world
  /// @param medium Medium to add
  void addMedium(Medium* medium);
};

#endif