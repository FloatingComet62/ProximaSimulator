#include "vectors.hpp"

v2::v2(float i, float j) {
  this->i = i;
  this->j = j;
}

// v2::v2(v3 vec3) {
//   this->i = vec3.i;
//   this->j = vec3.j;
// }

v3::v3(float i, float j, float k) {
  this->i = i;
  this->j = j;
  this->k = k;
}

v3::v3(v2 vec2) {
  this->i = vec2.i;
  this->j = vec2.j;
  this->k = 0;
}

float dot(v3 vec1, v3 vec2) {
  return vec1.i * vec2.i + vec1.j * vec2.j + vec1.k * vec2.k;
}

// vec1 = ai + bj + ck
// vec2 = di + ej + fk
// crossVec =>
// | a d i |
// | b e j |
// | c f k |
// crossVec = (bf-ce)i - (af-cd)j + (ae-bd)k
v3 cross(v3 vec1, v3 vec2) {
  v3 v(vec1.j * vec2.k - vec1.k * vec2.j, -vec1.i * vec2.k + vec1.k * vec2.i,
       vec1.i * vec2.j - vec1.j * vec2.i);
  return v;
}