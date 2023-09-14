#ifndef C_MESH_RENDER
#define C_MESH_RENDER

#include "../component.hpp"
#include "../window.hpp"

class MeshRenderType {};

class MeshRender : public Component {
 public:
  Window* window;
  Color color;

  MeshRender(World* world, Object* object, Window* window, Color color);
  static std::string getName();
  void Start() override;
  void Update() override;
};

#endif