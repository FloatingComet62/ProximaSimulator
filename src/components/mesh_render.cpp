#include "mesh_render.hpp"

#include "../object.hpp"
#include "../world.hpp"
#include "../optional.hpp"
#include "transform.hpp"

MeshRender::MeshRender(World* world, Object* object, Window* window,
                       Color* color)
    : Component(world, object) {
  this->color = color;
  this->transform = nullptr;
}

std::string MeshRender::getName() { return "mesh_render"; }

void MeshRender::start() {
  Optional<Component*> transform = this->object->getComponent(Components::TRANSFORM);
  if (!transform.hasValue()) return;
  this->transform = (Transform*)transform.getData();
}

void MeshRender::update() {
  if (Error::getInstance()->hasError()) return;
  if (this->transform == nullptr) {
    return;
  }

  int width = 50;
  int height = 50;

  auto pos = this->transform->position;

  int top_x = pos.i - width;
  int top_y = pos.j - height;

  for (int i = top_x; i < top_x + width; i++) {
    for (int j = top_y; i < top_y + height; j++) {
      this->window->setPixel(i, j, this->color);
    }
  }
}
