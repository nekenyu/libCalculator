#ifndef CALCULATOR_H
#define CALCULATOR_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {
  
  class Stack;
  class StackOperatorFactory;
  
  /** \class Executive
   * \brief Drivable class to run the calculator with a variable factory per
   * process call to support changing command sets.
   */
  class Executive {
  public:
    /** Create with the stack to process
     *
     * @param stack to process
     */
    Executive(Stack& stack);
    
    Executive(const Executive&) = delete;
    Executive(Executive&&) = delete;
    Executive& operator=(const Executive&) = delete;
    Executive& operator=(Executive&&) = delete;
    
    /** @return string representation of the current state */
    std::string toString() const;

    /** Process commands from input and pushing generated info to output
     *
     * @param factory to parse input and generate Operators from
     * @param input to read commands from
     * @param output to write status to
     */
    void process(StackOperatorFactory& factory, istream& input, ostream& output);

    /** Process commands from input and pushing generated info to output
     *
     * @param factory to parse input and generate Operators from
     * @param input to create one operator and execute from
     *
     * @return string output of processing the command for input.  An empty
     * return indicates that quit was requested.
     */
    std::string process(StackOperatorFactory& factory, const std::string& input);

    /** Process oper upon the Stack.
     *
     * @param oper to process on the Stack
     *
     * @return string output of processing the command for input.  An empty
     * return indicates that quit was requested.
     */
    std::string process(StackOperator::Ptr oper);
    
    /** @return the count of processed operations */
    unsigned int getOperationCount() const;

    /** Generate help info for this executive to output.
     *
     * @param factory providing commands to get help from
     * @param output to write help info to
     */
    void doHelp(const StackOperatorFactory& factory, ostream& output) const;

  private:
    Stack& stack;
    unsigned int operationCount;
  };

  /** \class FixedOperatorExecutive
   * \brief Drivable class to run the calculator with a single set of commands.
   */
  class FixedOperatorExecutive {
  public:
    FixedOperatorExecutive(StackOperatorFactory& theFactory, Stack& theStack);

    FixedOperatorExecutive(const Executive&) = delete;
    FixedOperatorExecutive(Executive&&) = delete;
    FixedOperatorExecutive& operator=(const Executive&) = delete;
    FixedOperatorExecutive& operator=(Executive&&) = delete;
    
    void doHelp(ostream& output) const;

    /** Process commands from input and pushing generated info to output
     *
     * @param input to read commands from
     * @param output to write status to
     */
    void process(istream& input, ostream& output);

    /** Process commands from input and pushing generated info to output
     *
     * @param input to create one operator and execute from
     *
     * @return string output of processing the command for input.  An empty
     * return indicates that quit was requested.
     */
    std::string process(const std::string& input);

  private:
    Executive executive;
    StackOperatorFactory& factory;
  };
  
} // namespace Calculator

#endif // CALCULATOR_H
