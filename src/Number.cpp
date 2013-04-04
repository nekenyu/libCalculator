#include <memory>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <initializer_list>

#include "Stack.h"
#include "Number.h"

namespace {

  std::string format(float f) {
    std::ostringstream os;
    os << f;
    return os.str();
  }

} // anonymous namespace

namespace Calculator {

  Number::Ptr Number::create(float theValue) {
    return Ptr(new Number(theValue));
  }

  Number::~Number() {
  }
  
  Number::Number(float theValue)
    : value(theValue), valueString(format(theValue))
  {
  }
  
  float Number::getValue() const {
    return value;
  }
  
  std::string Number::toString() const {
    return valueString;
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
	return Number::create(f);
      }
    }

    return StackOperator::Ptr();
  }

} // namespace Calculator
