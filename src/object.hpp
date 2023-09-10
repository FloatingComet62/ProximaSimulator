#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "component.hpp"
#include "vectors.hpp"
#include "world.hpp"

class Object {
 private:
  World world;

 public:
  v2 position;
  v2 velocity;
  v2 acceleration;
  std::vector<Component> components;

  Object();
};

#endif