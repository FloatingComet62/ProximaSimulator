#ifndef COMPONENT
#define COMPONENT

#include "color.hpp"
#include "vectors.hpp"

/// @attention THANK YOU
/// https://pvigier.github.io/2018/02/09/dependency-graph.html
class World;
class Object;

enum Components { TRANSFORM, MESH_RENDER };

/// @brief Convert Components to string
std::string componentsToString(int componentType);

/// # Component
/// @brief An abstract component
class Component {
 protected:
  World* world;
  Object* object;

 public:
  Component(World* world, Object* object);

  void setWorld(World* world);
  void setObject(Object* object);

  /// @brief Get the name of the component
  /// @example Transform Component will return "transform"
  /// @return The name of the component
  static std::string getName();

  /// @brief Start function is called once at startup
  virtual void start();

  /// @brief Update function is called every loop
  virtual void update();
};

#endif