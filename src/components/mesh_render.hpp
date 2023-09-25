#ifndef C_MESH_RENDER
#define C_MESH_RENDER

#include "../component.hpp"
#include "../window.hpp"
#include "transform.hpp"

class MeshRenderType {};

class MeshRender : public Component {
 private:
  Transform* transformOfObj;

 public:
  Window* window;
  Color color;

  MeshRender(World* world, Object* object, Window* window, Color color);
  static std::string getName();
  void start() override;
  void update() override;
};

#endif