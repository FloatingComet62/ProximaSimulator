#ifndef OBJECT
#define OBJECT

#include <optional>
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
  std::optional<Component> getComponent(int componentType);
};

#endif