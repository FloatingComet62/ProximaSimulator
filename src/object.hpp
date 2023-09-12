#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "component.hpp"
#include "transform.hpp"
#include "world.hpp"

class Object {
 private:
  World world;

 public:
  Transform transform;
  std::vector<Component> components;

  Object();
};

#endif