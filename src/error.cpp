#include "error.hpp"

std::string errorCodesToString(int code) {
  switch (code) {
    case ErrorCodes::NONE:
      return "None";

    case ErrorCodes::TESTING:
      return "Testing";

    case ErrorCodes::INVALID_HEX_STRING:
      return "Invalid Hex String";

    default:
      return "Unknown";
  }
}

Error& Error::getInstance() {
  static Error instance;
  return instance;
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