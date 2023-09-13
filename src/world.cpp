#include "world.hpp"

World::World(float gravity) { this->gravity = gravity; }

void World::addObject(Object object) { this->objects.push_back(object); }

void World::addMedium(Medium medium) { this->mediums.push_back(medium); }