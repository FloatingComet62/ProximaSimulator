#ifndef COMPONENT_H
#define COMPONENT_H

#include "vectors.hpp"

/// @attention THANK YOU
/// https://pvigier.github.io/2018/02/09/dependency-graph.html
class World;
class Object;

/// # Component
/// @brief An abstract component
class Component {
 protected:
  World* world;
  Object* owner;

 public:
  Component(World* world, Object* owner);

  void setWorld(World* world);
  void setOwner(Object* owner);

  /// @brief Start function is called once at startup
  virtual void Start();

  /// @brief Update function is called every loop
  virtual void Update();
};

class Transform {
 public:
  v2 position;
  v2 velocity;
  v2 acceleration;
  float rotation;

  Transform(v2 position, v2 velocity, v2 acceleration, float rotation);
  void Start();
  void Update();
};

#endif