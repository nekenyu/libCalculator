#ifndef VARIABLE_H
#define VARIABLE_H

#ifndef STACK_ITEM_H
#include "StackItem.h"
#endif // STACK_ITEM_H

namespace Calculator {
  
  class Stack;
  
  /** StackItem representing a variable.
   *
   * These are not re-used and the current value is not modified after creation.
   */
  class Variable : public StackItem {
  public:
    typedef std::shared_ptr<Variable> Ptr;

    /** Create with theName to represent.
     *
     * @param theName to be stored in this
     *
     * @return the Variable created
     */
    static Variable::Ptr create(const std::string& theName);

    virtual ~Variable();

  protected:
    /** Create with theName to represent.
     *
     * @param theName to be stored in this
     */
    Variable(const std::string& theName);

    Variable() = delete;
    Variable(const Variable&) = delete;
    Variable(Variable&&) = delete;
    Variable& operator=(const Variable&) = delete;
    Variable& operator=(Variable&&) = delete;
      
  public:
    /** @return the name of this Variable */
    const std::string& getName() const;

    virtual std::string toString() const;
    
  private:
    /** The name this represents */
    const std::string name;
  };

  /** Creates Variables from strings that convert to variables */
  class VariableCreator : public StackOperatorCreator {
  public:
    virtual ~VariableCreator();
 
    virtual std::string getHelp() const;
    virtual StackOperator::Ptr create(const std::string& str);
  };
  
} // namespace Calculator

#endif // VARIABLE_H
