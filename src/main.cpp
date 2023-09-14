#define SDL_MAIN_HANDLED

#define NUM_OF_SDLK_DOWN_EVENTS 322

#include <iostream>
#include <string>

#include "color.hpp"
#include "window.hpp"

int frameCount = 0;

/// @brief Error screen display
/// @param window Window to display on
void errorScreen(Window *window) {
  // I think the cool pattern fits as a error screens
  Color color(0, 0, 0);
  for (int i = 0; i < window->width; i++) {
    for (int j = 0; j < window->height; j++) {
      float c = frameCount % 255;
      color.red += i + c;
      color.green += j + c;
      color.blue += i + c;
      window->setPixel(i, j, &color);
    }
  }
  frameCount++;
  window->update();
}

Color color("#3ede69");

/// @brief Loop which should run every frame
/// @param window Window to update
void loop(Window *window) {
  if (Error::getInstance()->hasError()) {
    errorScreen(window);
    return;
  }
  for (int i = 0; i < window->width; i++) {
    for (int j = 0; j < window->height; j++) {
      window->setPixel(i, j, &color);
    }
  }
  frameCount++;
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

int main() {
  Window *window = new Window("Proxima Simulation", 800, 600);

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
    loop(window);
  }

  return 0;
}