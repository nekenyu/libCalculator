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

    /** Qualify an error with a stack position.
     *
     * @param position from the top, with 0 being the top
     * @param error message at position
     *
     * @return error message
     */
    inline std::string atPosition(unsigned int position, const std::string& error) {
      return std::string("At position ") + (0 == position ? std::string("top") : std::to_string(position)) + ": " + error;
    }

    /** Operation required a variable.  Item was not a variable. */
    const std::string NotAVariable = "Value is not a variable";

    /** Operation required a variable.  Variable has not been set. */
    const std::string VariableNotSet = "Variable is not set";

    /** Operation required a Number.  Item was not available. */
    const std::string NotANumber = "Value is not a number";
  };
  
} // namespace Calculator

#endif // ERROR_H
  
