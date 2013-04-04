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

    /** Operation required a variable.  Item was not a variable. */
    const std::string NotAVariable = "Value is not a variable";

    /** Operation required a variable.  Variable has not been set. */
    const std::string VariableNotSet = "Variable is not set";
  };
  
} // namespace Calculator

#endif // ERROR_H
  
