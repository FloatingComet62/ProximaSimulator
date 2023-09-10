#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color {
 public:
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;

  Color(uint8_t red, uint8_t green, uint8_t blue);
  Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
  Color(std::string hex_string);
  uint8_t* toArray();
};

#endif