#ifndef STACK_ITEM_H
#define STACK_ITEM_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {
  
  class Stack;

  /** \class StackItem
   * \brief Base class of all items that can be on the stack.
   */
  class StackItem : public StackOperator {
  public:
    typedef std::shared_ptr<StackItem> Ptr;
    
    virtual ~StackItem();
    
    /** Execute this item modifying stack.
     *
     * @param stack to process on
     * @param ofThis the StackOperator::Ptr for this object so that its info
     * can be passed around.
     */
    virtual std::string operator()(Stack& stack, StackOperator::Ptr ofThis);

    /** @return string representation of this */
    virtual std::string toString() const = 0;
  };
  
} // namespace Calculator

# endif // STACK_ITEM_H
