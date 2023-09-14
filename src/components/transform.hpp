#ifndef C_TRANSFORM
#define C_TRANSFORM

#include "../component.hpp"

class Transform : public Component {
 public:
  v2 position;
  v2 velocity;
  v2 acceleration;
  float rotation;

  Transform(World* world, Object* object, v2 position, v2 velocity,
            v2 acceleration, float rotation);
  static std::string getName();
  void Start() override;
  void Update() override;
};

#endif