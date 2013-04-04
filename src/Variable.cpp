#include <memory>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "Stack.h"
#include "Variable.h"

namespace Calculator {

  Variable::Ptr Variable::create(const std::string& theName) {
    return Ptr(new Variable(theName));
  }

  Variable::~Variable() {
  }
  
  Variable::Variable(const std::string& theName)
    : name(theName)
  {
  }

  const std::string& Variable::getName() const {
    return name;
  }

  std::string Variable::toString() const {
    return name;
  }

  VariableCreator::~VariableCreator() { }

  std::string VariableCreator::getHelp() const {
    return "$<name> -- Variable of name <name>";
  }

  StackOperator::Ptr VariableCreator::create(const std::string& str) {
    if(0 == str.find('$')) {
      return Variable::create(str);
    }

    return StackOperator::Ptr();
  }

} // namespace Calculator
