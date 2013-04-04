#ifndef BINARY_MATH_OPERATOR_H
#define BINARY_MATH_OPERATOR_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {

  /** Stack Modifier for Binary Math Operations.
   *
   * Support multiple operations distinguished by the Operation parameter.
   *
   * All Operations pop 2 items, caclulate formerTop (operator) formerSecond
   * and push the result back onto the stack.
   */
  class BinaryMathOperator : public StackOperator {
  public:
    typedef std::shared_ptr<BinaryMathOperator> Ptr;

    /** \enum Operation Operations supported */
    enum class Operation {
      /** Add the two values */
      ADD,

	/** Subtract the two values */
	SUBTRACT,
	
	/** Multiply the two values */
	MULTIPLY,
	
	/** Divide the two values */
	DIVIDE,
	
	/** Raise top to the exponent second */
	EXPONENT
	};

    /** Create to perform operation.
     *
     * @param op to perform
     *
     * @return BinaryMathOperator created
     */
    static BinaryMathOperator::Ptr create(Operation op);

    ~BinaryMathOperator();

  protected:
    /** Create to perform operation.
     *
     * @param op to perform
     */
    BinaryMathOperator(Operation op);
    
    BinaryMathOperator(const BinaryMathOperator&) = delete;
    BinaryMathOperator(BinaryMathOperator&&) = delete;
    BinaryMathOperator& operator=(const BinaryMathOperator&) = delete;
    BinaryMathOperator& operator=(BinaryMathOperator&&) = delete;

  public:
    virtual std::string operator()(Stack& stack, StackOperator::Ptr ofThis);
    
  private:
    const Operation op;
  };

  /** Create BinaryMathOperation from a string */
  class BinaryMathCreator : public StackOperatorCreator {
  public:
    virtual ~BinaryMathCreator();
 
    virtual std::string getHelp() const;
    virtual StackOperator::Ptr create(const std::string& str);
  };
} // namespace Calculator

#endif // BINARY_MATH_OPERATOR_H
