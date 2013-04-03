#ifndef STACK_OPERATOR_H
#define STACK_OPERATOR_H

namespace Calculator {

  class Stack;
  
  /** \brief Base class for all operators.
   *
   * StackOperatorCreators and the StackFactory will return StackOperator::Ptr.
   */
  class StackOperator {
  public:
    typedef std::shared_ptr<StackOperator> Ptr;

    virtual ~StackOperator() { }
    
    /** Execute this operator on stack
     *
     * @param stack to operate on
     * @param ofThis is this in a copied StackOperator::Ptr to maintain
     * integrity of the shared_ptrs.
     *
     * @return string result of execution.  Can be any string.  Common strings
     * are listed in Calculator::Errorh
     */
    virtual std::string operator()(Stack& stack, StackOperator::Ptr ofThis) = 0;
  };

  /** \brief Factory creators of StackOperator::Ptrs
   */
  class StackOperatorCreator {
  public:
    typedef std::shared_ptr<StackOperatorCreator> Ptr;
    
    virtual ~StackOperatorCreator() { }

    /** @return Help text for StackOperator::Ptrs this creates */
    virtual std::string getHelp() const = 0;

    /** @return StackOperator::Ptr of the StackOperator created from str, or
     * it will be empty to indicate str cannot be used to create an item of
     * this type.
     */
    virtual StackOperator::Ptr create(const std::string& str) = 0;
  };
  
} // namespace Calculator 

#endif // STACK_OPERATOR_H
