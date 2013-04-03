#include <memory>
#include <vector>
#include <string>
#include <sstream>

#include "Stack.h"
#include "Number.h"

namespace Calculator {

  Number::~Number() {
  }
  
  Number::Number(float theValue)
    : value(theValue)
  {
  }
  
  float Number::getValue() const {
    return value;
  }
  
  std::string Number::toString() const {
    return std::to_string(value);
  }

  NumberCreator::~NumberCreator() { }

  std::string NumberCreator::getHelp() const {
    return "[number] -- Any of many formats of number to push onto the stack";
  }

  StackOperator::Ptr NumberCreator::create(const std::string& str) {
    std::istringstream is(str);
    float f = 0.0;
    is >> f;

    if(is) {
      char c;
      is >> c;
      if(is.eof()) {
	return StackOperator::Ptr(new Number(f));
      }
    }

    return StackOperator::Ptr();
  }

} // namespace Calculator
