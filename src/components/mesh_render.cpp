#include "mesh_render.hpp"

#include "object.hpp"
#include "world.hpp"

MeshRender::MeshRender(World* world, Object* object, Window* window,
                       Color color)
    : Component(world, object) {
  this->color = color;
}
std::string MeshRender::getName() { return "mesh_render"; }
void MeshRender::Start() {}
void MeshRender::Update() {}