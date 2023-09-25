#ifndef OBJECT
#define OBJECT

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
  Component getComponent(int componentType);
  void update();
};

#endif
