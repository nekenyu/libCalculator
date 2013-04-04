#include <memory>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "Stack.h"
#include "Variable.h"

namespace Calculator {

  Variable::~Variable() {
  }
  
  Variable::Variable(const std::string& theName)
    : name(theName)
  {
  }

  const std::string& Variable::getName() const {
    return name;
  }

  float Variable::getValue() const {
    return 0.0; // TODO: implement this
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
      return StackOperator::Ptr(new Variable(str));
    }

    return StackOperator::Ptr();
  }

} // namespace Calculator
