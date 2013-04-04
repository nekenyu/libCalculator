#ifndef NUMBER_H
#define NUMBER_H

#ifndef STACK_ITEM_H
#include "StackItem.h"
#endif // STACK_ITEM_H

namespace Calculator {
  
  class Stack;
  
  /** StackItem representing a number.
   *
   * These are not re-used and the current value is not modified after creation.
   */
  class Number : public StackItem {
  public:
    typedef std::shared_ptr<Number> Ptr;

    virtual ~Number();

    /** Create with theValue to represent.
     *
     * @param theValue to be stored in this
     */
    Number(float theValue);
    
    virtual float getValue() const;
    virtual std::string toString() const;
    
  private:
    /** The value this represents */
    const float value;

    /** The value this represents */
    const std::string valueString;
  };

  /** Creates Numbers from strings that convert to numbers */
  class NumberCreator : public StackOperatorCreator {
  public:
    virtual ~NumberCreator();
 
    virtual std::string getHelp() const;
    virtual StackOperator::Ptr create(const std::string& str);
  };
  
} // namespace Calculator

#endif // NUMBER_H
