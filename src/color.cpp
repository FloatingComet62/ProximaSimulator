#include "color.hpp"

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
      case 8:
      case 6:
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
    Error::getInstance().sendError(ErrorCodes::INVALID_HEX_STRING,
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