#ifndef VARIABLE_MANIPULATOR_H
#define VARIABLE_MANIPULATOR_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {

  /** Variable Modifier for Variable Operations
   *
   * Support multiple operations distinguished by the Operation parameter.
   *
   * Operations support separate variable-element manipulations
   */
  class VariableManipulator : public StackOperator {
  public:
    typedef std::shared_ptr<VariableManipulator> Ptr;

    /** \enum Operation Operations supported */
    enum class Operation {
      /** Write the value in next-to-top to variable in top*/
      WRITE,

	/** Replace the top variable with its value */
	READ
      };
    
    /** Create to perform operation.
     *
     * @param op to perform
     *
     * @return VariableManipulator created
     */
    static VariableManipulator::Ptr create(Operation op);

    ~VariableManipulator();

  protected:
    /** Create to perform operation.
     *
     * @param op to perform
     */
    VariableManipulator(Operation op);
    
    VariableManipulator(const VariableManipulator&) = delete;
    VariableManipulator(VariableManipulator&&) = delete;
    VariableManipulator& operator=(const VariableManipulator&) = delete;
    VariableManipulator& operator=(VariableManipulator&&) = delete;

    virtual std::string operator()(Stack& stack, StackOperator::Ptr ofThis);
    
  private:
    const Operation op;
  };

  /** Create VariableManipulator from a string */
  class VariableManipulatorCreator : public StackOperatorCreator {
  public:
    virtual ~VariableManipulatorCreator();
 
    virtual std::string getHelp() const;
    virtual StackOperator::Ptr create(const std::string& str);
  };
} // namespace Calculator

#endif // VARIABLE_MANIPULATOR_H
