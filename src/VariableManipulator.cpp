#include <memory>
#include <vector>
#include <string>
#include <map>

#include "Error.h"
#include "VariableManipulator.h"
#include "Variable.h"
#include "Number.h"
#include "Stack.h"

namespace Calculator {

  VariableManipulator::~VariableManipulator() {
  }

  VariableManipulator::VariableManipulator(Operation operation)
    :op(operation)
  {
  }
  
  std::string VariableManipulator::operator()(Stack& stack, StackOperator::Ptr ofThis) {
    if(Operation::WRITE == op) {
      if(stack.getDepth() < 2) {
	return Error::StackUnderflow;
      }
      
      Variable::Ptr variable;
      StackItem::Ptr value;
      StackIterator iter = stack.begin();
      iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> variable
	   >> value;
      // stack.popAfter() deferred until after variable evaluation

      if(!variable) {
	return Error::NotAVariable;
      }
      stack.popAfter(iter);

      stack.getVariables().set(variable->getName(), value);

      return Error::Ok;
    } else if(Operation::READ == op) {
      if(stack.getDepth() < 1) {
	return Error::StackUnderflow;
      }
      
      Variable::Ptr variable;
      StackIterator iter = stack.begin();
      iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> variable;
      // stack.popAfter() deferred until after variable evaluation

      if(!variable) {
	return Error::NotAVariable;
      }

      StackItem::Ptr result = stack.getVariables().get(variable->getName());
      if(!result) {
	return Error::VariableNotSet;
      }
      stack.popAfter(iter);

      (*result)(stack, result);
      return Error::Ok;
    } else {
      // Internal error....  Not sure what to do.
      return "Internal Error: Missing VariableManipulator.";
    }
  }

  VariableManipulatorCreator::~VariableManipulatorCreator() {
  }

  std::string VariableManipulatorCreator::getHelp() const {
    return std::string() + 
      "! -- write to the variable top element the value beneath it\n" +
      "@ -- replace the top variable with its value";
  }

  StackOperator::Ptr VariableManipulatorCreator::create(const std::string& str) {
    VariableManipulator::Operation op = VariableManipulator::Operation::WRITE;
    if(0 == str.compare("!")) {
      op = VariableManipulator::Operation::WRITE;
    } else if(0 == str.compare("@")) {
      op = VariableManipulator::Operation::READ;
    } else {
      return StackOperator::Ptr();
    }

    return StackOperator::Ptr(new VariableManipulator(op));
  }

} // namespace Calculator
