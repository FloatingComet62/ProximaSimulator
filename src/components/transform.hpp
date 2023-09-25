#ifndef C_TRANSFORM
#define C_TRANSFORM

#include "../component.hpp"

class Transform : public Component {
 public:
  v2 position;
  v2 velocity;
  v2 acceleration;
  float rotation;

  Transform(World* world, Object* object, v2 position = v2(),
            v2 velocity = v2(), v2 acceleration = v2(), float rotation = 0.0);
  static std::string getName();
  void start() override;
  void update() override;
};

#endif