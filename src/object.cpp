#include "object.hpp"

#include "component.hpp"
#include "error.hpp"
#include "world.hpp"

Object::Object(World* world) { this->world = world; }

void Object::addComponent(Component* component) {
  this->components.push_back(component);
}

Optional<Component*> Object::getComponent(int componentType) {
  std::string componentStr = componentsToString(componentType);
  for (auto& component : this->components) {
    if (component->getName() == componentStr) return Optional<Component*>(component);
  }
  Error::getInstance()->sendError(ErrorCodes::TRANSFORM_NOT_FOUND, "Transform not found");
  return Optional<Component*>();
}

void Object::update() {
  for (auto& component : this->components) {
    component->update();
  }
}
