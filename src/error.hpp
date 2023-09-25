#ifndef ERROR
#define ERROR

#include <iostream>
#include <string>

enum ErrorCodes {
  NONE = 0,
  TESTING = 1,
  SDL_ERROR = 2,
  INVALID_HEX_STRING = 3,
  TRANSFORM_NOT_FOUND = 4
};

/// @brief Convert ErrorCodes to Strings
/// @param code ErrorCode
/// @return Stringified ErrorCode
std::string errorCodesToString(int code);

/// # Error
/// @brief Global Error management system
class Error {
 private:
  bool isError;
  int errorCode;
  std::string errorMessage;

  static Error* instance;
  Error() {}

 public:
  Error(Error const*) = delete;
  void operator=(Error const*) = delete;

  /// @brief Get the singleton instance of Error
  /// @return Singleton instance
  static Error* getInstance();

  /// @brief Send an error
  /// @param errorCode Error code
  /// @param errorMessage Error message
  void sendError(int errorCode, std::string errorMessage);

  /// @brief Clear the error
  void clearError();

  /// @brief Check if there exists an error
  /// @return True if an error exists
  bool hasError();
};

#endif
