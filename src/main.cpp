#define SDL_MAIN_HANDLED

#define NUM_OF_SDLK_DOWN_EVENTS 322

#include <iostream>
#include <string>
#include <vector>

#include "../deps/include/SDL.h"

// ----- HEADER ------
// -------------------
// H_ERROR

enum ErrorCodes {
  NONE = 0,
  TESTING = 1,
  SDL_ERROR = 2,
  INVALID_HEX_STRING = 3,
  TRANSFORM_NOT_FOUND = 4
};

/// @brief Convert ErrorCodes to Strings
/// @param code ErrorCode
/// @return Stringified ErrorCode
std::string errorCodesToString(int code);

/// # Error
/// @brief Global Error management system
class Error {
 private:
  bool isError;
  int errorCode;
  std::string errorMessage;

  static Error* instance;
  Error() {}

 public:
  Error(Error const*) = delete;
  void operator=(Error const*) = delete;

  /// @brief Get the singleton instance of Error
  /// @return Singleton instance
  static Error* getInstance();

  /// @brief Send an error
  /// @param errorCode Error code
  /// @param errorMessage Error message
  void sendError(int errorCode, std::string errorMessage);

  /// @brief Clear the error
  void clearError();

  /// @brief Check if there exists an error
  /// @return True if an error exists
  bool hasError();
};

// -------------------
// H_COLOR

/// # Color
/// @brief Color representation
class Color {
 public:
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;

  /// @brief Initialize a color with rgb values
  /// @param red Amount of Red
  /// @param green Amount of Green
  /// @param blue Amount of Blue
  Color(uint8_t red, uint8_t green, uint8_t blue);

  /// @brief Initialize a color with rgba values
  /// @param red Amount of Red
  /// @param green Amout of Green
  /// @param blue Amount of Blue
  /// @param alpha Amount of Alpha
  Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

  /// @brief Initialize a color with hex string
  /// @param hex_string Hex string
  /// @exception Sends an error if hex is invalid
  Color(std::string hex_string);

  /// @brief Convert to string
  /// @return The string
  std::string to_string();
};

// -------------------
// H_OPTIONAL

/// # Optional
/// @brief Option<> in rust
template<class T>
class Optional {
 private:
  /// @brief Does contain actual value
  bool has_value;
  
  /// @brief Data
  T data;

 public:
  /// @brief Initialize None
  Optional();

  /// @brief Initialize Some
  /// @param data Data to store
  Optional(T data);

  /// isSome
  /// @return Does contain value
  bool hasValue();

  /// unwrap data
  /// @return Data inside the class
  T getData();

  /// @brief Convert to string
  /// @return The string
  std::string to_string();
};

// -------------------
// H_VECTOR

/// # Vector 2D
/// @brief 2 dimentional vector
class v2 {
 public:
  float i;
  float j;

  /// @brief Initialize a 2d vector
  /// @param i X coordinate (i cap)
  /// @param j Y coordinate (j cap)
  v2(float i = 0, float j = 0);

  v2 operator+(v2 const& obj) {
    v2 res;
    res.i = this->i + obj.i;
    res.j = this->j + obj.j;
    return res;
  }
  v2 operator-(v2 const& obj) {
    v2 res;
    res.i = this->i - obj.i;
    res.j = this->j - obj.j;
    return res;
  }

  /// @brief Convert to string
  /// @return The string
  std::string to_string();
};

/// # Vector 3D
/// @brief 3 dimentional vector
class v3 {
 public:
  float i;
  float j;
  float k;

  /// @brief Initialize a 3D vector
  /// @param i X coordinate (i cap)
  /// @param j Y cooridnate (j cap)
  /// @param k Z coordinate (j cap)
  v3(float i = 0, float j = 0, float k = 0);
  v3(v2 vec2);

  v3 operator+(v3 const& obj) {
    v3 res;
    res.i = this->i + obj.i;
    res.j = this->j + obj.j;
    res.k = this->k + obj.k;
    return res;

  /// @brief Convert to string
  /// @return The string
  }
  v3 operator-(v3 const& obj) {
    v3 res;
    res.i = this->i - obj.i;
    res.j = this->j - obj.j;
    res.k = this->k - obj.k;
    return res;
  }

  /// @brief Convert to string
  /// @return The string
  std::string to_string();
};

float dot(v3 vec1, v3 vec2);
v3 cross(v3 vec1, v3 vec2);

// -------------------
// H_MEDIUM

/// # Medium
/// @brief The medium that will surround the objects in the world
class Medium {
 private:
  v2 top_left;
  v2 bottom_right;

 public:
  float viscosity;
  
  Medium(float viscosity);

  /// @brief Convert to string
  /// @return The string
  std::string to_string();
};

// -------------------
// H_COMPONENT

class World;
class Object;

enum Components { TRANSFORM, MESH_RENDER, NIL };

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
  virtual std::string getName();

  /// @brief Start function is called once at startup
  virtual void start();

  /// @brief Update function is called every loop
  virtual void update();

  /// @brief Convert to string
  /// @return The string
  virtual std::string to_string();
};

// -------------------
// H_TRANSFORM

class v2;

class Transform : public Component {
 public:
  v2 position;
  v2 velocity;
  v2 acceleration;
  float rotation;

  Transform(World* world, Object* object, v2 position = v2(),
            v2 velocity = v2(), v2 acceleration = v2(), float rotation = 0.0);
  std::string getName() override;
  void start() override;
  void update() override;
  std::string to_string() override;
};

// -------------------
// H_MESHRENDER

class Window;
class Color;

// class MeshRenderType {};

class MeshRender : public Component {
 private:
  Transform* transform;

 public:
  Window* window;
  Color* color;

  MeshRender(World* world, Object* object, Window* window, Color* color);
  std::string getName() override;
  void start() override;
  void update() override;
  std::string to_string() override;
};

// -------------------
// H_OBJECT

class Object {
 private:
  World* world;

 public:
  std::vector<Component*> components;

  Object(World* world);
  ~Object();

  /// @brief Add a component
  /// @param component Component to add
  void addComponent(Component* component);

  /// @brief Add a vector of components
  /// @param components Vector of components
  void addComponents(std::vector<Component*> components);

  /// @brief Get a component by component type
  /// @param componentType Specify the component type
  /// @return Optional Component pointer, because the component might not exist
  Optional<Component*> getComponent(int componentType);

  /// @brief Initialize the object
  void start();

  /// @brief Update the object every loop
  void update();

  /// @brief Convert to string
  /// @return The string
  std::string to_string();
};

// -------------------
// H_WORLD

class Window;

/// # World
/// @brief The world environment
class World {
 private:
  Window* window;

 public:
  std::vector<Object*> objects;
  std::vector<Medium*> mediums;
  float gravity;

  /// @brief Initialize the world
  /// @param window Window to display the world
  /// @param gravity Gravity of the world
  World(Window* window, float gravity = 0);

  ~World();
  
  /// @brief Start code to run for objects and mediums
  void start();

  /// @brief Update objects and mediums every frame
  void update();

  /// @brief Add an object to the world
  /// @param object Object to add
  void addObject(Object* object);

  /// @brief Add an object to the world
  /// @param objects List of objects to add
  void addObjects(std::vector<Object*> objects);

  /// @brief Add a medium to the world
  /// @param medium Medium to add
  void addMedium(Medium* medium);

  /// @brief Add a medium to the world
  /// @param mediums List of mediums to add
  void addMediums(std::vector<Medium*> mediums);

  /// @brief Convert to string
  /// @return The string
  std::string to_string();
};

// -------------------
// H_WINDOW

/// # SDL Window Manager
/// @brief Handes the renderer, texture, and pixel data
/// @authors FloatinComet62 SpaceFishDev
class Window {
 private:
  SDL_Window *winPtr;
  SDL_Renderer *rendererPtr;
  SDL_Texture *texturePtr;
  uint8_t *pixels;

 public:
  /// @brief Width of the window
  int width;
  /// @brief Height of the window
  int height;

  /// @brief Initialize a window
  /// @param title Title of the window
  Window(std::string title, int width, int height);
  Window(std::string title, int width, int height, std::string icon);

  /// @brief Update the pixel buffer
  /// @param x X coordinate
  /// @param y Y coordinate
  /// @param color Color to set at that pixel
  void setPixel(int x, int y, Color *color);

  /// @brief Get the color of the pixel
  /// @param x X coordinate
  /// @param y Y coordinate
  /// @return The color at that pixel
  Color getPixel(int x, int y);

  /// @brief Flush the pixels buffer on the screen
  void update();
};

// H_END
// -------------------
// D_START

// -------------------
// D_COLOR

uint8_t intFromHexChar(char c) {
  if ((c >= '0') && (c <= '9')) return c - '0';
  if ((c >= 'A') && (c <= 'F')) return 10 + c - 'A';
  if ((c >= 'a') && (c <= 'f')) return 10 + c - 'a';
  return 'q';
}

// examples i wrote before i coded the function below
// 17 -> 1 * 16 + 7 = 23
// a8 -> 10 * 16 + 8 = 168
uint8_t hexFromStr(std::string str) {
  return intFromHexChar(str[0]) * 16 + intFromHexChar(str[1]);
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue) {
  this->red = red;
  this->green = green;
  this->blue = blue;
  this->alpha = 255;
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
  this->red = red;
  this->green = green;
  this->blue = blue;
  this->alpha = alpha;
}

Color::Color(std::string hex_string) {
  if (hex_string[0] == '#') hex_string.erase(0, 1);
  std::string parsed_string;
  {
    int hex_len = hex_string.length();
    switch (hex_len) {
      case 3:
      case 4:
        for (auto& character : hex_string) {
          parsed_string += character;
          parsed_string += character;
        }
        break;
      case 6:
      case 8:
        parsed_string += hex_string;
        break;

      default:
        break;
    }
    if (hex_len == 3 || hex_len == 6) {
      parsed_string += "ff";  // for alpha
    }
  }

  if (parsed_string.length() != 8) {
    // some weird invalid hex was provided
    std::string errorMessage = hex_string;
    errorMessage += " is not a valid hex string\n";
    Error::getInstance()->sendError(ErrorCodes::INVALID_HEX_STRING,
                                    errorMessage);
    this->red = 0;
    this->green = 0;
    this->blue = 0;
    this->alpha = 0;
    return;
  }

  this->red = hexFromStr(parsed_string.substr(0, 2));
  this->green = hexFromStr(parsed_string.substr(2, 2));
  this->blue = hexFromStr(parsed_string.substr(4, 2));
  this->alpha = hexFromStr(parsed_string.substr(6, 2));
}

std::string Color::to_string() {
  std::string address = std::to_string((unsigned long long)(void**)this);
  std::string msg = "Color(addr: ";
  msg += address; msg += ", red: ";
  msg += std::to_string(this->red); msg += ", green: ";
  msg += std::to_string(this->green); msg += ", blue :";
  msg += std::to_string(this->blue);
  msg += ")";
  return msg;
}

// -------------------
// D_ERROR

std::string errorCodesToString(int code) {
  switch (code) {
    case ErrorCodes::NONE:
      return "None";

    case ErrorCodes::SDL_ERROR:
      return "SDL Error";

    case ErrorCodes::TESTING:
      return "Testing";

    case ErrorCodes::INVALID_HEX_STRING:
      return "Invalid Hex String";

    default:
      return "Unknown";
  }
}

Error* Error::getInstance() {
  static Error instance;
  return &instance;
}

void Error::clearError() {
  this->errorCode = ErrorCodes::NONE;
  this->errorMessage = "";
  this->isError = false;
}

void Error::sendError(int errorCode, std::string errorMessage) {
  if (errorCode == this->errorCode) {
    // it's the same error again, ignore it
    return;
  }

  this->isError = true;
  this->errorCode = errorCode;
  this->errorMessage = errorMessage;

  std::cout << "Error Code: " << errorCodesToString(errorCode)
            << "\nError received: " << errorMessage << std::endl;
}

bool Error::hasError() { return this->isError; }

// -------------------
// D_OPTIONAL

template<class T>
Optional<T>::Optional() {
  this->has_value = false;
  this->data = nullptr;
}

template<class T>
Optional<T>::Optional(T data) {
  this->has_value = true;
  this->data = data;
}

template<class T>
bool Optional<T>::hasValue() {
  return this->has_value;
}

template<class T>
T Optional<T>::getData() {
  return this->data;
}

template<class T>
std::string Optional<T>::to_string() {
  std::string msg = "";
  if (this->has_value) {
    msg += "Some(";
    msg += this->data->to_string();
    msg += ")";
  } else {
    msg += "None";
  }
  return msg;
}

// -------------------
// D_VECTOR

v2::v2(float i, float j) {
  this->i = i;
  this->j = j;
}

std::string v2::to_string() {
  std::string msg = "v2(addr: ";
  std::string address = std::to_string((unsigned long long)(void**)this);
  msg += address; msg += ", i: ";
  msg += std::to_string(this->i); msg += ", j: ";
  msg += std::to_string(this->j);
  msg += ")";
  return msg;
}

v3::v3(float i, float j, float k) {
  this->i = i;
  this->j = j;
  this->k = k;
}

v3::v3(v2 vec2) {
  this->i = vec2.i;
  this->j = vec2.j;
  this->k = 0;
}

std::string v3::to_string() {
  std::string msg = "v3(addr: ";
  std::string address = std::to_string((unsigned long long)(void**)this);
  msg += address; msg += ", i: ";
  msg += std::to_string(this->i); msg += ", j: ";
  msg += std::to_string(this->j); msg += ", k: ";
  msg += std::to_string(this->k);
  msg += ")";
  return msg;
}

float dot(v3 vec1, v3 vec2) {
  return vec1.i * vec2.i + vec1.j * vec2.j + vec1.k * vec2.k;
}

// vec1 = ai + bj + ck
// vec2 = di + ej + fk
// crossVec =>
// | a d i |
// | b e j |
// | c f k |
// crossVec = (bf-ce)i - (af-cd)j + (ae-bd)k
v3 cross(v3 vec1, v3 vec2) {
  v3 v(vec1.j * vec2.k - vec1.k * vec2.j, -vec1.i * vec2.k + vec1.k * vec2.i,
       vec1.i * vec2.j - vec1.j * vec2.i);
  return v;
}

// -------------------
// D_MEDIUM

Medium::Medium(float viscosity) {
  this->viscosity = viscosity;
}

std::string Medium::to_string() {
  std::string msg = "Medium(addr: ";
  std::string address = std::to_string((unsigned long long)(void**)this);
  msg += address; msg += ", viscosity: ";
  msg += std::to_string(this->viscosity);
  msg += ")";
  return msg;
}

// -------------------
// D_COMPONENT

std::string componentsToString(int componentType) {
  switch (componentType) {
    case Components::TRANSFORM:
      return "transform";

    case Components::MESH_RENDER:
      return "mesh_render";

    case Components::NIL:
      return "none";

    default:
      break;
  }
  return "none";
}

Component::Component(World* world, Object* object) { this->world = world; }

void Component::setWorld(World* world) { this->world = world; }

void Component::setObject(Object* object) { this->object = object; }

std::string Component::getName() { return componentsToString(Components::NIL); }

void Component::start(){};

void Component::update(){};

std::string Component::to_string() {
  std::string msg = "Component(addr: ";
  std::string address = std::to_string((unsigned long long)(void**)this);
  msg += address;
  msg += ")";
  return msg;
}

// -------------------
// D_TRANSFORM

Transform::Transform(World* world, Object* object, v2 position, v2 velocity,
                     v2 acceleration, float rotation)
    : Component(world, object) {
  this->position = position;
  this->velocity = velocity;
  this->acceleration = acceleration;
  this->rotation = rotation;
}

std::string Transform::getName() { return componentsToString(Components::TRANSFORM); }

void Transform::start() {
}

void Transform::update() {
  if (Error::getInstance()->hasError()) return;
}

std::string Transform::to_string() {
  std::string msg = "Transform(addr: ";
  std::string address = std::to_string((unsigned long long)(void**)this);
  msg += address; msg += ", position: ";
  msg += this->position.to_string(); msg += ", rotation: ";
  msg += std::to_string(this->rotation); msg += ", velocity: ";
  msg += this->velocity.to_string(); msg += ", acceleration: ";
  msg += this->acceleration.to_string();
  msg += ")";
  return msg;
}

// -------------------
// D_MESHRENDER

MeshRender::MeshRender(World* world, Object* object, Window* window,
                       Color* color)
    : Component(world, object) {
  this->color = color;
  this->transform = nullptr;
}

std::string MeshRender::getName() { return componentsToString(Components::MESH_RENDER); }

void MeshRender::start() {
  std::cout << &this->object->components << " before function call\n";
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

std::string MeshRender::to_string() {
  std::string msg = "MeshRender(addr: ";
  std::string address = std::to_string((unsigned long long)(void**)this);
  msg += address; msg += ", transform: ";
  msg += this->transform->to_string(); msg += ", color: ";
  msg += this->color->to_string();
  msg += ")";
  return msg;
}

// -------------------
// D_OBJECT

Object::Object(World* world) {
  this->world = world;
  this->components.clear();
}
Object::~Object() {
  for (int i = 0; i < this->components.size(); i++) {
    free(this->components[i]);
  }
}

void Object::addComponent(Component* component) {
  this->components.push_back(component);
}

void Object::addComponents(std::vector<Component*> components) {
  for (auto& component : components) {
    this->addComponent(component);
  }
}

Optional<Component*> Object::getComponent(int componentType) {
  std::string componentStr = componentsToString(componentType);
  for (auto& component : this->components) {
    std::cout << &this->components << " inside function call\n";
    std::cout << component->to_string() << " ";
    if (component->getName() == componentStr) return Optional<Component*>(component);
  }
  Error::getInstance()->sendError(ErrorCodes::TRANSFORM_NOT_FOUND, "Transform not found");
  return Optional<Component*>();
}

void Object::start() {
  for (auto& component : this->components) {
    component->start();
  }
}

void Object::update() {
  for (auto& component : this->components) {
    component->update();
  }
}

std::string Object::to_string() {
  std::string msg = "MeshRender(addr: ";
  std::string address = std::to_string((unsigned long long)(void**)this);
  msg += address; msg += ", components: [";
  for (int i = 0; i < this->components.size(); i++) {
    auto component = this->components[i];
    msg += component->to_string();
    if ((i+1) != this->components.size()) {
      msg += ", ";
    }
  }
  msg += "]";
  msg += ")";
  return msg;
}

// -------------------
// D_WORLD

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

void World::start() {
  for (auto& object : this->objects) {
    object->start();
  }
}

void World::update() {
  for (auto& object : this->objects) {
    object->update();
  }
}

void World::addObject(Object* object) { this->objects.push_back(object); }

void World::addObjects(std::vector<Object*> objects) {
  for (auto& object : objects) {
    this->addObject(object);
  }
}

void World::addMedium(Medium* medium) { this->mediums.push_back(medium); }

void World::addMediums(std::vector<Medium*> mediums) {
  for (auto& medium : mediums) {
    this->addMedium(medium);
  }
}

std::string World::to_string() {
  std::string msg = "MeshRender(addr: ";
  std::string address = std::to_string((unsigned long long)(void**)this);
  msg += address; msg += ", objects: [";
  for (int i = 0; i < this->objects.size(); i++) {
    auto object = this->objects[i];
    msg += object->to_string();
    if ((i+1) != this->objects.size()) {
      msg += ", ";
    }
  }
  msg += ", mediums: [";
  for (int i = 0; i < this->mediums.size(); i++) {
    auto medium = this->mediums[i];
    msg += medium->to_string();
    if ((i+1) != this->mediums.size()) {
      msg += ", ";
    }
  }
  msg += "]";
  msg += ")";
  return msg;
}

// -------------------
// D_WINDOW

Window::Window(std::string title, int width, int height) {
  this->width = width;
  this->height = height;
  SDL_Init(SDL_INIT_VIDEO);
  pixels = new uint8_t[this->width * this->height * 4];  // 4 bytes for color
  SDL_CreateWindowAndRenderer(this->width, this->height, 0, &this->winPtr,
                              &this->rendererPtr);
  this->texturePtr =
      SDL_CreateTexture(this->rendererPtr, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, this->width, this->height);
  SDL_SetWindowTitle(this->winPtr, title.c_str());
  SDL_SetWindowResizable(this->winPtr, SDL_TRUE);
}

Window::Window(std::string title, int width, int height, std::string icon) : Window(title, width, height) {
  SDL_Surface *img = SDL_LoadBMP(icon.c_str());
  SDL_SetWindowIcon(this->winPtr, img);
}

void Window::setPixel(int x, int y, Color *color) {
  if (x < 0 || x > this->width) return;
  if (y < 0 || y > this->height) return;

  // BGRA
  this->pixels[4 * (y * this->width + x) + 0] = color->blue;
  this->pixels[4 * (y * this->width + x) + 1] = color->green;
  this->pixels[4 * (y * this->width + x) + 2] = color->red;
  this->pixels[4 * (y * this->width + x) + 3] = color->alpha;
}

Color Window::getPixel(int x, int y) {
  if (!this->pixels) return Color(0, 0, 0, 0);

  int blue = this->pixels[4 * (y * this->width + x) + 0];
  int green = this->pixels[4 * (y * this->width + x) + 1];
  int red = this->pixels[4 * (y * this->width + x) + 2];
  int alpha = this->pixels[4 * (y * this->width + x) + 3];

  return Color(red, green, blue, alpha);
}

void Window::update() {
  if ((SDL_GetWindowFlags(this->winPtr) & SDL_WINDOW_INPUT_FOCUS) == 0) return;
  if ((!this->texturePtr) || (!this->rendererPtr)) return;

  SDL_UpdateTexture(this->texturePtr, 0, this->pixels, 4 * this->width);
  SDL_RenderCopy(this->rendererPtr, this->texturePtr, 0, 0);
  SDL_RenderPresent(this->rendererPtr);
  SDL_RenderClear(this->rendererPtr);
}

// -------------------
// D_END
// M_START

int frame_count = 0;

// Grid Config
bool show_grid = true;
Color grid_color("#777");
int grid_size = 50;


Color bg_color("#090909");
std::vector<World*> worlds;

// M_WIN_ERROR

/// @brief Error screen display
/// @param window Window to display on
void errorScreen(Window *window) {
  // I think the cool pattern fits as a error screens
  Color color(0, 0, 0);
  for (int i = 0; i < window->width; i++) {
    for (int j = 0; j < window->height; j++) {
      float c = frame_count % 255;
      color.red += i + c;
      color.green += j + c;
      color.blue += i + c;
      window->setPixel(i, j, &color);
    }
  }
  frame_count++;
  window->update();
}

// M_WIN_LOOP

/// @brief Loop which should run every frame
/// @param window Window to update
void loop(Window *window) {
  if (Error::getInstance()->hasError()) {
    errorScreen(window);
    return;
  }

  for (int i = 0; i < window->width; i++) {
    for (int j = 0; j < window->height; j++) {
      window->setPixel(i, j, &bg_color);

      if (
          show_grid &&
          (
            (i % grid_size == 0) ||
            (j % grid_size == 0)
          )
        ) {
        window->setPixel(i, j, &grid_color);
      }
    }
  }

  frame_count++;
  window->update();
}

// M_KEYS

/// @brief Handler for key presses
/// @param keys Array of key presses
/// @attention https://stackoverflow.com/a/3816128/15058455
void handle_keys(bool *keys) {
  // if uncommented, pressing s is display the crash screen
  if (keys[SDLK_s]) {
    Error::getInstance()->sendError(ErrorCodes::TESTING, "S key was pressed");
  } else if (keys[SDLK_c]) {
    Error::getInstance()->clearError();
  }
}

// M_CHECK_ERROR

void check_for_sdl_errors() {
  std::string sdl_error = SDL_GetError();
  if (sdl_error.length() != 0) {
    Error::getInstance()->sendError(ErrorCodes::SDL_ERROR, sdl_error);
  }
}

int main() {

  // M_INIT
  Window *window = new Window("Proxima Simulation", 1200, 700, "ProximaSimulator.bmp");

  /// @attention https://stackoverflow.com/a/3816128/15058455
  bool KEYS[NUM_OF_SDLK_DOWN_EVENTS];
  for (int i = 0; i < NUM_OF_SDLK_DOWN_EVENTS; i++) {
    KEYS[i] = false;
  }

  int running = true;

  World world{window, 9.8};
  Object obj{&world};
  Transform transform{&world, &obj, v2(100, 100)};
  Color color("#542e7d");
  MeshRender mesh_render{&world,&obj, window, &color};
  obj.addComponents(std::vector<Component*>{&transform, &mesh_render});
  world.addObject(&obj);

  worlds.push_back(&world);


  for (auto &world : worlds) {
    world->start();
  }

  // M_LOOP

  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;

        case SDL_KEYDOWN:
          KEYS[event.key.keysym.sym] = true;
          break;

        case SDL_KEYUP:
          KEYS[event.key.keysym.sym] = false;
          break;

        default:
          break;
      }
    }

    handle_keys(KEYS);
    check_for_sdl_errors();
    loop(window);


    for (auto &world : worlds) {
      world->update();
    }
  }

  for (auto& world : worlds) {
    free(world);
  }

  return 0;
}
