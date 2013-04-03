#include <memory>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "Executive.h"
#include "Stack.h"
#include "StackOperatorFactory.h"

namespace Calculator {

Executive::~Executive() {
}

Executive::Executive(Stack& theStack)
  : stack(theStack), operationCount(0)
{
}

void Executive::process(StackOperatorFactory& factory, istream& input, ostream& output) {
  output << toString() << endl;
  while(true) {
    std::string command;
    input >> command;
    if(!input) {
      break;
    }

    const std::string result = process(factory, command);
    if(result.empty()) {
      output << "User requested quit..." << endl;
      return;
    }

    output << ">> " << operationCount << ": " << result << endl;
    output << toString() << endl;
  }
}

std::string Executive::toString() const {
  return std::string("Stack: ") + stack.toString();
}

std::string Executive::process(StackOperatorFactory& factory, const std::string& input) {
  if(0 == input.compare("quit")) {
    return "";
  }

 if(0 == input.compare("help")) {
    std::ostringstream os;
    os << "Help" << endl;
    doHelp(os);
    return os.str();
  }
  
  StackOperator::Ptr op = factory.create(input);
  if(!op) {
    return std::string("Ignoring invalid input: \"") + input + "\"";
  }
  
  return process(op);
}

std::string Executive::process(StackOperator::Ptr oper) {
  if(!oper) {
    return "Internal Error: Invalid Operator";
  }

  const std::string result = (*oper)(stack, oper);

  ++operationCount;

  return result;
}

unsigned int Executive::getOperationCount() const {
  return operationCount;
}

void Executive::doHelp(ostream& output) const {
  output << "Stack-based calculator." << endl;
  output << "Commands:" << endl;
  output << "\tquit -- exit the program" << endl;
  output << "\thelp -- help for the program" << endl;
}

FixedOperatorExecutive::FixedOperatorExecutive(StackOperatorFactory& theFactory, Stack& theStack)
    : Executive(theStack), factory(theFactory)
    {
    }

void FixedOperatorExecutive::doHelp(ostream& output) const {
  Executive::doHelp(output);

  output << endl;
  output << factory.getHelp();
}

void FixedOperatorExecutive::process(istream& input, ostream& output) {
  Executive::process(factory, input, output);
}

std::string FixedOperatorExecutive::process(const std::string& input) {
  return Executive::process(factory, input);
}

} // namespace Caclulator
