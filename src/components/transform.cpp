#include "transform.hpp"

#include "object.hpp"
#include "world.hpp"

Transform::Transform(World* world, Object* object, v2 position, v2 velocity,
                     v2 acceleration, float rotation)
    : Component(world, object) {
  this->position = position;
  this->velocity = velocity;
  this->acceleration = acceleration;
  this->rotation = rotation;
}
std::string Transform::getName() { return "transform"; }
void Transform::Start() {}
void Transform::Update() {}