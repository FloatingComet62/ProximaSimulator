#define SDL_MAIN_HANDLED

#define WIDTH 800
#define HEIGHT 600

#define NUM_OF_SDLK_DOWN_EVENTS 322

#include <iostream>
#include <string>

#include "../deps/include/SDL.h"
#include "color.hpp"

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
  /// @brief Initialize a window
  /// @param title Title of the window
  Window(std::string title) {
    SDL_Init(SDL_INIT_VIDEO);
    pixels = new uint8_t[WIDTH * HEIGHT * 4];  // 4 bytes for color
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &this->winPtr,
                                &this->rendererPtr);
    this->texturePtr =
        SDL_CreateTexture(this->rendererPtr, SDL_PIXELFORMAT_ARGB8888,
                          SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    SDL_SetWindowTitle(this->winPtr, title.c_str());
  }

  /// @brief Update the pixel buffer
  /// @param x X coordinate
  /// @param y Y coordinate
  /// @param color Color to set at that pixel
  void setPixel(int x, int y, Color *color) {
    // BGRA
    this->pixels[4 * (y * WIDTH + x) + 0] = color->blue;
    this->pixels[4 * (y * WIDTH + x) + 1] = color->green;
    this->pixels[4 * (y * WIDTH + x) + 2] = color->red;
    this->pixels[4 * (y * WIDTH + x) + 3] = color->alpha;
  }

  /// @brief Get the color of the pixel
  /// @param x X coordinate
  /// @param y Y coordinate
  /// @return The color at that pixel
  Color getPixel(int x, int y) {
    int blue = this->pixels[4 * (y * WIDTH + x) + 0];
    int green = this->pixels[4 * (y * WIDTH + x) + 1];
    int red = this->pixels[4 * (y * WIDTH + x) + 2];
    int alpha = this->pixels[4 * (y * WIDTH + x) + 3];

    return Color(red, green, blue, alpha);
  }

  /// @brief Flush the pixels buffer on the screen
  void update() {
    SDL_UpdateTexture(this->texturePtr, 0, this->pixels, 4 * WIDTH);
    SDL_RenderCopy(this->rendererPtr, this->texturePtr, 0, 0);
    SDL_RenderPresent(this->rendererPtr);
    SDL_RenderClear(this->rendererPtr);
  }
};

int frameCount = 0;

/// @brief Error screen display
/// @param window Window to display on
void errorScreen(Window *window) {
  // I think the cool pattern fits as a error screens
  Color color(0, 0, 0);
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      float c = ((float)i / WIDTH) * (frameCount % 255);
      color.red += i;
      color.green += j;
      color.blue += i * j;
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
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
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
    Error::getInstance()->sendError(ErrorCodes::TESTING, "");
  } else if (keys[SDLK_c]) {
    Error::getInstance()->clearError();
  }
}

int main() {
  Window *window = new Window("Proxima Simulation");

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