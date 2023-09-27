#include "world.hpp"

World::World(Window* window, float gravity) {
  this->window = window;
  this->gravity = gravity;
}

World::~World() {
  for (int i = 0; i < this->objects.size(); i++) {
    free(this->objects[i]);
  }
  for (int i = 0; i < this->mediums.size(); i++) {
    free(this->mediums[i]);
  }
}

void World::addObject(Object* object) { this->objects.push_back(object); }

void World::addMedium(Medium* medium) { this->mediums.push_back(medium); }
