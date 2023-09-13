#include "component.hpp"

#include "object.hpp"
#include "world.hpp"

Component::Component(World* world, Object* owner) { this->world = world; }
void Component::setWorld(World* world) { this->world = world; }
void Component::setOwner(Object* owner) { this->owner = owner; }

void Component::Start(){};
void Component::Update(){};

Transform::Transform(v2 position, v2 velocity, v2 acceleration,
                     float rotation) {
  this->position = position;
  this->velocity = velocity;
  this->acceleration = acceleration;
  this->rotation = rotation;
}
void Transform::Start(){};
void Transform::Update(){};