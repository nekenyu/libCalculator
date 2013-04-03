#include <memory>
#include <vector>
#include <string>
#include <map>

#include "Error.h"
#include "StackManipulator.h"
#include "Number.h"
#include "Stack.h"

namespace Calculator {

  StackManipulator::~StackManipulator() {
  }

  StackManipulator::StackManipulator(Operation operation)
    :op(operation)
  {
  }
  
  std::string StackManipulator::operator()(Stack& stack, StackOperator::Ptr ofThis) {
    if(Operation::POP == op) {
      StackItem::Ptr values[1];
      if(!stack.pop(1, values)) {
	return Error::StackUnderflow;
      }
      
      return Error::Ok;
    } else if(Operation::DUP == op) {
      StackItem::Ptr values[1];
      if(!stack.pop(1, values)) {
	return Error::StackUnderflow;
      }
      
      (*values[0])(stack, values[0]);
      (*values[0])(stack, values[0]);
      return Error::Ok;
    } else if(Operation::SWAP == op) {
      StackItem::Ptr values[2];
      if(!stack.pop(2, values)) {
	return Error::StackUnderflow;
      }
      (*values[0])(stack, values[0]);
      (*values[1])(stack, values[1]);
      return Error::Ok;
    } else {
      // Internal error....  Not sure what to do.
      return "Internal Error: Missing StackManipulator.";
    }
  }

  StackManipulatorCreator::~StackManipulatorCreator() {
  }

  std::string StackManipulatorCreator::getHelp() const {
    return std::string() + 
      "pop -- remove the top element\n" +
      "dup -- add a copy of the top element\n" +
      "swap -- exchange the top two values on the stack";
  }

  StackOperator::Ptr StackManipulatorCreator::create(const std::string& str) {
    StackManipulator::Operation op = StackManipulator::Operation::POP;
    if(0 == str.compare("pop")) {
      op = StackManipulator::Operation::POP;
    } else if(0 == str.compare("dup")) {
      op = StackManipulator::Operation::DUP;
    } else if(0 == str.compare("swap")) {
      op = StackManipulator::Operation::SWAP;
    } else {
      return StackOperator::Ptr();
    }

    return StackOperator::Ptr(new StackManipulator(op));
  }

} // namespace Calculator
