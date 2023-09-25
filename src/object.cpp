#include "object.hpp"

#include "world.hpp"

Object::Object(World* world) { this->world = world; }

void Object::addComponent(Component component) {
  this->components.push_back(component);
}

Component Object::getComponent(int componentType) {
  std::string componentStr = componentsToString(componentType);
  for (auto& component : this->components) {
    if (component.getName() == componentStr) return component;
  }
  std::cout << componentStr << " not found" << std::endl;
  std::exit(0);
}

void Object::update() {
  for (auto& component : this->components) {
    component.update();
  }
}
