#include "object.hpp"

#include "world.hpp"

Object::Object(World* world) { this->world = world; }

void Object::addComponent(Component component) {
  this->components.push_back(component);
}

std::optional<Component> Object::getComponent(int componentType) {
  std::string componentStr = componentsToString(componentType);
  for (auto& component : components) {
    if (component.getName() == componentStr) return component;
  }
  return std::nullopt;
}