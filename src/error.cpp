#include "error.hpp"

Error& Error::getInstance() {
  static Error instance;
  return instance;
}
void Error::clearError() {
  this->errorCode = 0;
  this->errorMessage = "";
  this->isError = false;
}

void Error::sendError(int errorCode, std::string errorMessage) {
  if (errorCode == this->errorCode) {
    // it's the same error again, ignore
    return;
  }

  this->isError = true;
  this->errorCode = errorCode;
  this->errorMessage = errorMessage;

  std::cout << "Error Code: " << errorCode
            << "\nError received: " << errorMessage << std::endl;
}
bool Error::hasError() { return this->isError; }