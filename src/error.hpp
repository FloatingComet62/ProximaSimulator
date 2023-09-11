#ifndef ERROR_H
#define ERROR_H

#include "string"

class Error {
 private:
  bool isError;
  int errorCode;
  std::string errorMessage;

  static Error* instance;
  Error() {}

 public:
  Error(Error const&) = delete;
  void operator=(Error const&) = delete;
  static Error& getInstance();
  void sendError(int errorCode, std::string errorMessage);
  void clearError();
  bool hasError();
};

#endif