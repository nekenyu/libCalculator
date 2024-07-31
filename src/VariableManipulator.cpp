/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <memory>
#include <string>
#include <vector>

#include "Error.h"
#include "VariableManipulator.h"
#include "Variable.h"
#include "VariableSet.h"
#include "Number.h"
#include "Stack.h"

namespace Calculator {

  VariableManipulator::Ptr VariableManipulator::create(Operation op) {
    return Ptr(new VariableManipulator(op));
  }

  VariableManipulator::~VariableManipulator() {
  }

  VariableManipulator::VariableManipulator(Operation operation)
    :op(operation)
  {
  }
  
  Result VariableManipulator::operator()(Stack& stack, StackOperator::Ptr ofThis) {
    if(Operation::WRITE == op) {
      Variable::Ptr variable;
      StackItem::Ptr value;
      StackIterator iter = stack.begin();
      iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> variable
	   >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> value;
      // stack.popAfter() deferred until after variable evaluation

      if(!iter) {
	return iter.getResult();
      }

      stack.popAfter(iter);

      stack.getVariables().set(variable->getName(), value);

      return Result({Error::Ok});
    } else if(Operation::READ == op) {
      Variable::Ptr variable;
      StackIterator iter = stack.begin();
      iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> variable;
      // stack.popAfter() deferred until after variable evaluation

      if(!variable) {
	// Already detected non variable, just return errors
	return iter.getResult();
      }

      StackItem::Ptr result = stack.getVariables().get(variable->getName());
      if(!result) {
	// Error not detected by iter, add it
	iter.addError(0, Error::VariableNotSet);
      }
      if(!iter) {
	return iter.getResult();
      }

      stack.popAfter(iter);

      (*result)(stack, result);
      return Result({Error::Ok});
    }

    // Internal error....  Not sure what to do.
    return Result({"Internal Error: Missing VariableManipulator."});
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

    return VariableManipulator::create(op);
  }

} // namespace Calculator
