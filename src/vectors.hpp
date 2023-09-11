#ifndef VEC_H
#define VEC_H

class v2 {
 public:
  float i;
  float j;

  v2(float i = 0, float j = 0);
  v2 operator+(v2 const& obj) {
    v2 res;
    res.i = this->i + obj.i;
    res.j = this->j + obj.j;
    return res;
  }
};
class v3 {
 public:
  float i;
  float j;
  float k;

  v3(float i = 0, float j = 0, float k = 0);
  v3(v2 vec2);
  v3 operator+(v3 const& obj) {
    v3 res;
    res.i = this->i + obj.i;
    res.j = this->j + obj.j;
    res.k = this->k + obj.k;
    return res;
  }
};

float dot(v3 vec1, v3 vec2);
v3 cross(v3 vec1, v3 vec2);

#endif