#ifndef COMPONENT_H
#define COMPONENT_H

#include "object.hpp"

class Component {
 private:
  World world;
  Object owner;

 public:
  Component(Object owner, World world);

  // Start function is called once at startup
  virtual void Start();

  // Update function is called every loop
  virtual void Update();
};

#endif