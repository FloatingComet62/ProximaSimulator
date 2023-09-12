#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "error.hpp"

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
};

#endif