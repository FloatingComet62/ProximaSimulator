#include "window.hpp"

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
