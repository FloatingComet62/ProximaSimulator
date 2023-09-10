#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "object.hpp"

class World {
 private:
  std::vector<Object> objects;

 public:
  float gravity;

  World();
  void addObject(Object object);
};

#endif