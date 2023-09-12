#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vectors.hpp"

class Transform {
 public:
  v2 position;
  v2 velocity;
  v2 acceleration;
  float rotation;
};

#endif