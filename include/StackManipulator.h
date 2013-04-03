#ifndef STACK_MANIPULATOR_H
#define STACK_MANIPULATOR_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {

  /** Stack Modifier for Stack Operations
   *
   * Support multiple operations distinguished by the Operation parameter.
   *
   * Operations support separate stack-element manipulations
   */
  class StackManipulator : public StackOperator {
  public:
    /** \enum Operation Operations supported */
    enum class Operation {
      /** Pop the top value off and forget it */
      POP,

	/** Duplicate the top value */
	DUP,
	
	/** Swap the top two elements */
	SWAP
	};
    
    ~StackManipulator();

    /** Create to perform operation.
     *
     * @param operation to perform
     */
    StackManipulator(Operation operation);
    
    StackManipulator(const StackManipulator&) = delete;
    StackManipulator(StackManipulator&&) = delete;
    StackManipulator& operator=(const StackManipulator&) = delete;
    StackManipulator& operator=(StackManipulator&&) = delete;

    virtual std::string operator()(Stack& stack, StackOperator::Ptr ofThis);
    
  private:
    const Operation op;
  };

  /** Create StackManipulator from a string */
  class StackManipulatorCreator : public StackOperatorCreator {
  public:
    virtual ~StackManipulatorCreator();
 
    virtual std::string getHelp() const;
    virtual StackOperator::Ptr create(const std::string& str);
  };
} // namespace Calculator

#endif // STACK_MANIPULATOR_H
