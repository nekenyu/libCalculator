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

    /** Create with theValue to represent.
     *
     * @param theValue to be stored in this
     *
     * @return Number created
     */
    static Number::Ptr create(float theValue);

    virtual ~Number();
    
   protected:
    /** Create with theValue to represent.
     *
     * @param theValue to be stored in this
     */
    Number(float theValue);

    Number() = delete;
    Number(const Number&) = delete;
    Number(Number&&) = delete;
    Number& operator=(const Number&) = delete;
    Number& operator=(Number&&) = delete;
      
  public:
    /** @return the value this represents */
    float getValue() const;

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
