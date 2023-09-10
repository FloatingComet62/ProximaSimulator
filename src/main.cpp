#define SDL_MAIN_HANDLED
#define WIDTH 800
#define HEIGHT 600

#include <iostream>
#include <string>

#include "../deps/include/SDL.h"
#include "color.hpp"

class Window {
 private:
  SDL_Window *winPtr;
  SDL_Renderer *rendererPtr;
  SDL_Texture *texturePtr;
  uint8_t *pixels;

 public:
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
  void setPixel(int x, int y, Color *color) {
    // BGRA
    this->pixels[4 * (y * WIDTH + x) + 0] = color->blue;
    this->pixels[4 * (y * WIDTH + x) + 1] = color->green;
    this->pixels[4 * (y * WIDTH + x) + 2] = color->red;
    this->pixels[4 * (y * WIDTH + x) + 3] = color->alpha;
  }
  void update() {
    SDL_UpdateTexture(this->texturePtr, 0, this->pixels, 4 * WIDTH);
    SDL_RenderCopy(this->rendererPtr, this->texturePtr, 0, 0);
    SDL_RenderPresent(this->rendererPtr);
    SDL_RenderClear(this->rendererPtr);
  }
};

int frameCount = 0;

void loop(Window *window) {
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

int main() {
  Window *window = new Window("Proxima Simulation");

  int running = true;
  while (running) {
    SDL_Event event;
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT) {
      running = false;
    }
    loop(window);
  }

  return 0;
}