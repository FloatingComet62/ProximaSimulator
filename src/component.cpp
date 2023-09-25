#include "component.hpp"

#include "components/mesh_render.hpp"
#include "components/transform.hpp"
#include "object.hpp"
#include "world.hpp"

std::string componentsToString(int componentType) {
  switch (componentType) {
    case Components::TRANSFORM:
      return "transform";

    case Components::MESH_RENDER:
      return "mesh_render";

    default:
      break;
  }
  return "none";
}

Component::Component(World* world, Object* object) { this->world = world; }

void Component::setWorld(World* world) { this->world = world; }

void Component::setObject(Object* object) { this->object = object; }

std::string Component::getName() { return "none"; }

void Component::start(){};

void Component::update(){};
