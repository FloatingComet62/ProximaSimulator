#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "component.hpp"

class World;

class Object {
 private:
  World* world;

 public:
  std::vector<Component> components;

  Object(World* world);
  void addComponent(Component component);
};

#endif