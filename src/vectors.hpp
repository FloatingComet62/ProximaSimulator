#ifndef VEC
#define VEC

/// # Vector 2D
/// @brief 2 dimentional vector
class v2 {
 public:
  float i;
  float j;

  /// @brief Initialize a 2d vector
  /// @param i X coordinate (i cap)
  /// @param j Y coordinate (j cap)
  v2(float i = 0, float j = 0);

  v2 operator+(v2 const& obj) {
    v2 res;
    res.i = this->i + obj.i;
    res.j = this->j + obj.j;
    return res;
  }
  v2 operator-(v2 const& obj) {
    v2 res;
    res.i = this->i - obj.i;
    res.j = this->j - obj.j;
    return res;
  }
};

/// # Vector 3D
/// @brief 3 dimentional vector
class v3 {
 public:
  float i;
  float j;
  float k;

  /// @brief Initialize a 3D vector
  /// @param i X coordinate (i cap)
  /// @param j Y cooridnate (j cap)
  /// @param k Z coordinate (j cap)
  v3(float i = 0, float j = 0, float k = 0);
  v3(v2 vec2);

  v3 operator+(v3 const& obj) {
    v3 res;
    res.i = this->i + obj.i;
    res.j = this->j + obj.j;
    res.k = this->k + obj.k;
    return res;
  }
  v3 operator-(v3 const& obj) {
    v3 res;
    res.i = this->i - obj.i;
    res.j = this->j - obj.j;
    res.k = this->k - obj.k;
    return res;
  }
};

float dot(v3 vec1, v3 vec2);
v3 cross(v3 vec1, v3 vec2);

#endif