#ifndef COMPONENT_H
#define COMPONENT_H

#include "object.hpp"

/// # Component
/// @brief An abstract component
class Component {
 private:
  World& world;
  Object& owner;

 public:
  /// @brief Initialize the component
  /// @param owner The object that this component is applied on
  /// @param world The world in which the object is
  Component(Object& owner, World& world);

  /// @brief Start function is called once at startup
  virtual void Start();

  /// @brief Update function is called every loop
  virtual void Update();
};

#endif