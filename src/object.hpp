#ifndef OBJECT
#define OBJECT

#include <vector>
#include <corecrt_malloc.h>

#include "component.hpp"
#include "optional.hpp"
#include "error.hpp"

class World;

class Object {
 private:
  World* world;

 public:
  std::vector<Component*> components;

  Object(World* world);
  ~Object();
  void addComponent(Component* component);
  Optional<Component*> getComponent(int componentType);
  void update();
};

#endif
