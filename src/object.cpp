#include "object.hpp"

#include "world.hpp"

Object::Object(World* world) { this->world = world; }
void Object::addComponent(Component component) {
  this->components.push_back(component);
}