#define SDL_MAIN_HANDLED

#define NUM_OF_SDLK_DOWN_EVENTS 322

#include <iostream>
#include <string>

#include "error.hpp"
#include "color.hpp"
#include "components/mesh_render.hpp"
#include "components/transform.hpp"
#include "window.hpp"
#include "component.hpp"
#include "world.hpp"

int frame_count = 0;

// Grid Config
bool show_grid = true;
Color grid_color("#777");
int grid_size = 50;


Color bg_color("#090909");
std::vector<World*> worlds;

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

  for (auto &world : worlds) {
    for (auto &obj : world->objects) {
      obj->update();
    }
  }

  frame_count++;
  window->update();
}

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

void check_for_sdl_errors() {
  std::string sdl_error = SDL_GetError();
  if (sdl_error.length() != 0) {
    Error::getInstance()->sendError(ErrorCodes::SDL_ERROR, sdl_error);
  }
}

int main() {
  Window *window = new Window("Proxima Simulation", 1200, 700, "ProximaSimulator.bmp");

  /// @attention https://stackoverflow.com/a/3816128/15058455
  bool KEYS[NUM_OF_SDLK_DOWN_EVENTS];
  for (int i = 0; i < NUM_OF_SDLK_DOWN_EVENTS; i++) {
    KEYS[i] = false;
  }

  int running = true;
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

    auto world = new World(window, 9.8);
    auto obj = new Object(world);
    auto transform = new Transform(world, obj, v2(100, 100));
    Color color = Color("#542e7d");
    auto mr = new MeshRender(world, obj, window, &color);
    obj->addComponent((Component*)transform);
    obj->addComponent((Component*)mr);
    world->addObject(obj);

    worlds.push_back(world);
  }

  for (auto& world : worlds) {
    free(world);
  }

  return 0;
}
