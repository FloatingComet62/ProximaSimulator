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
  this->isError = true;
  this->errorCode = errorCode;
  this->errorMessage = errorMessage;
}
bool Error::hasError() { return this->isError; }