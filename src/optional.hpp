#ifndef OPTIONAL
#define OPTIONAL

/// # Optional
/// @brief Option<> in rust
template<class T>
class Optional {
 private:
  /// @brief Does contain actual value
  bool has_value;
  
  /// @brief Data
  T data;

 public:
  /// @brief Initialize None
  Optional();

  /// @brief Initialize Some
  /// @param data Data to store
  Optional(T data);

  /// isSome
  /// @return Does contain value
  bool hasValue();

  /// unwrap data
  /// @return Data inside the class
  T getData();
};

#endif
