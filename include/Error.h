#ifndef ERROR_H
#define ERROR_H

namespace Calculator {

  /** \namespace Error
   * \brief Error / Return values of Stack Operations to ensure consistency.
   */
  namespace Error {
    /** Operation was successful */
    const std::string Ok = "Ok";

    /** Operation required more items than the Stack had available */
    const std::string StackUnderflow = "Insufficient Stack Arguments";
  };
  
} // namespace Calculator

#endif // ERROR_H
  
