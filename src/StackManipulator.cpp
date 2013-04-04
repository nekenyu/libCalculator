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
