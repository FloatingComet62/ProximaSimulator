#ifndef VEC_H
#define VEC_H

class v2 {
 public:
  float i;
  float j;

  v2(float i, float j);
  // v2(v3 vec3);
};
class v3 {
 public:
  float i;
  float j;
  float k;

  v3(float i, float j, float k);
  v3(v2 vec2);
};

float dot(v3 vec1, v3 vec2);
v3 cross(v3 vec1, v3 vec2);

#endif