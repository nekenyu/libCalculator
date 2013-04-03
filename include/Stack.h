#ifndef  STACK_H
#define  STACK_H

#ifndef STACK_ITEM_H
#include "StackItem.h"
#endif // STACK_ITEM_H

namespace Calculator {
  
  /** Stack of values to process from.
   *
   * Contains StackItem::Ptr objects.
   */
  class Stack {
  private:
    typedef std::vector<StackItem::Ptr> SubStack;
    typedef SubStack::iterator SubStackIter;
    typedef SubStack::const_iterator SubStackCIter;
    typedef SubStack::reverse_iterator SubStackRIter;

  public:
    /** Count of StackItems */
    typedef unsigned int Count;
    
    Stack();
    Stack(const Stack& rhs) = delete;
    Stack(Stack&& rhs) = delete;
    Stack& operator=(const Stack& rhs) = delete;
    Stack& operator=(Stack&& rhs) = delete;
    
    /** @return number of StackItems on the Stack */
    Count getDepth() const;

    /** Push item onto the stack
     *
     * @param item to push
     */
    void push(StackItem::Ptr item);
    
    /** Pop count items from stack and place into to.  If there are not enough
     * StackItems on the Stack, returns false and nothing is one.
     *
     * @param count of items to pop
     * @param to array[count] to receive items popped such that the last item
     * push()ed onto the stack is to[0].
     *
     * @return true if count items were popped, false if getDepth() < count.
     */
    bool pop(Count count, StackItem::Ptr* to);
    
    /** Create string representation of the current contents of the Stack */
    std::string toString() const;

  private:
    /** Implementation of the Stack */
    SubStack impl;
  };
  
} // namespace Calculator

#endif //  STACK_H
