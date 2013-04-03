#ifndef CALCULATOR_H
#define CALCULATOR_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {
  
  class Stack;
  class StackOperatorFactory;
  
  class Executive {
  public:
    ~Executive();
    Executive(Stack& stack);
    
    Executive(const Executive&) = delete;
    Executive(Executive&&) = delete;
    Executive& operator=(const Executive&) = delete;
    Executive& operator=(Executive&&) = delete;
    
    std::string toString() const;
    void process(StackOperatorFactory& factory, istream& input, ostream& output);
    std::string process(StackOperatorFactory& factory, const std::string& input);
    std::string process(StackOperator::Ptr oper);
    
    unsigned int getOperationCount() const;

    virtual void doHelp(ostream& output) const;

  private:
    Stack& stack;
    unsigned int operationCount;
  };

  class FixedOperatorExecutive : private Executive {
  public:
    FixedOperatorExecutive(StackOperatorFactory& theFactory, Stack& theStack);

    FixedOperatorExecutive(const Executive&) = delete;
    FixedOperatorExecutive(Executive&&) = delete;
    FixedOperatorExecutive& operator=(const Executive&) = delete;
    FixedOperatorExecutive& operator=(Executive&&) = delete;
    
    void doHelp(ostream& output) const;
    void process(istream& input, ostream& output);
    std::string process(const std::string& input);

  private:
    StackOperatorFactory& factory;
  };
  
} // namespace Calculator

#endif // CALCULATOR_H
