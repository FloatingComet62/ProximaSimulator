#ifndef WINDOW
#define WINDOW

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

#endif
