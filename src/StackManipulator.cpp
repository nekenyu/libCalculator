#include <memory>
#include <vector>
#include <string>
#include <map>

#include "Error.h"
#include "StackManipulator.h"
#include "Number.h"
#include "Stack.h"

namespace Calculator {

  StackManipulator::Ptr StackManipulator::create(Operation theOp) {
    return Ptr(new StackManipulator(theOp));
  }

  StackManipulator::~StackManipulator() {
  }

  StackManipulator::StackManipulator(Operation theOp)
    :op(theOp)
  {
  }
  
  std::string StackManipulator::operator()(Stack& stack, StackOperator::Ptr ofThis) {
    if(Operation::POP == op) {
      if(stack.getDepth() < 1) {
	return Error::StackUnderflow;
      }

      StackIterator iter = stack.begin();
      ++iter;
      stack.popAfter(iter);

      return Error::Ok;
    } else if(Operation::DUP == op) {
      if(stack.getDepth() < 1) {
	return Error::StackUnderflow;
      }

      StackItem::Ptr item;
      StackIterator iter = stack.begin();
      iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> item;
      // Do NOT stack.popAfter(iter) -- we are keeping it and duplicating it
      (*item)(stack, item);

      return Error::Ok;
    } else if(Operation::SWAP == op) {
      if(stack.getDepth() < 2) {
	return Error::StackUnderflow;
      }
      
      StackItem::Ptr first;
      StackItem::Ptr second;
      StackIterator iter = stack.begin();
      iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> first
	   >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> second;
      stack.popAfter(iter);
      
      (*first)(stack, first);
      (*second)(stack, second);

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

    return StackManipulator::create(op);
  }

} // namespace Calculator
