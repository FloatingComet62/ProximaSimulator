#include "mesh_render.hpp"

#include "object.hpp"
#include "world.hpp"

MeshRender::MeshRender(World* world, Object* object, Window* window,
                       Color color)
    : Component(world, object) {
  this->color = color;
  this->transformOfObj = nullptr;
}
std::string MeshRender::getName() { return "mesh_render"; }
void MeshRender::start() {
  auto optional_transform = this->object->getComponent(Components::TRANSFORM);
  if (!optional_transform.has_value()) {
    Error::getInstance()->sendError(ErrorCodes::TRANSFORM_NOT_FOUND,
                                    "MeshRender requires Transform");
    return;
  }
}
void MeshRender::update() {
  if (this->transformOfObj == nullptr) {
    return;
  }

  int width = 50;
  int height = 50;

  auto pos = this->transformOfObj->position;

  int top_x = pos.i - width;
  int top_y = pos.j - height;

  for (int i = top_x; i < top_x + width; i++) {
    for (int j = top_y; i < top_y + height; j++) {
      this->window->setPixel(i, j, &this->color);
    }
  }
}