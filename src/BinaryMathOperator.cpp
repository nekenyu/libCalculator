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
#include <map>

#include "math.h"

#include "BinaryMathOperator.h"
#include "Number.h"
#include "Stack.h"
#include "Error.h"

namespace {
  using namespace Calculator;

  /*
   * This is a whole lot to just use one array of ops to get math functions and
   * such....
   *
   * I wouldn't do it again unless there was a really long list....
   */
  class OpInfo {
  public:
    typedef std::function<float (float, float)> Function;

    OpInfo() {
    }

    OpInfo(BinaryMathOperator::Operation theOp, const std::string& theSymbol, Function theFunction)
      : op(theOp), symbol(theSymbol), function(theFunction)
    {
    }

    BinaryMathOperator::Operation getOp() const {
      return op;
    }

    std::string getSymbol() const {
      return symbol;
    }

    Function getFunction() const {
      return function;
    }

  private:
    BinaryMathOperator::Operation op;
    std::string symbol;
    Function function;
  };
  
  class OpInfoMap {
  private:
    typedef std::map<std::string, OpInfo> OpInfoBySymbol;
    typedef std::map<BinaryMathOperator::Operation, OpInfo> OpInfoByOp;

  public:
    OpInfoMap() {
      const OpInfo data[] = { 
	OpInfo(BinaryMathOperator::Operation::ADD, "+", [](float a, float b)->float { return a + b; }),
	OpInfo(BinaryMathOperator::Operation::SUBTRACT, "-", [](float a, float b)->float { return a - b; }),
	OpInfo(BinaryMathOperator::Operation::MULTIPLY, "*", [](float a, float b)->float { return a * b; }),
	OpInfo(BinaryMathOperator::Operation::DIVIDE, "/", [](float a, float b)->float { return a / b; }),
	OpInfo(BinaryMathOperator::Operation::EXPONENT, "^", [](float a, float b)->float { return pow(a, b); })
      };
      
      for(OpInfo info : data) {
	bySymbol[info.getSymbol()] = info;
	byOp[info.getOp()] = info;
      }
    }
    
    const OpInfo* operator[](std::string symbol) const {
      OpInfoBySymbol::const_iterator found = bySymbol.find(symbol);
      if(bySymbol.end() == found) {
	return nullptr;
      }
      return &found->second;
    }

    const OpInfo* operator[](BinaryMathOperator::Operation op) const {
      OpInfoByOp::const_iterator found = byOp.find(op);
      if(byOp.end() == found) {
	return nullptr;
      }
      return &found->second;
    }

  private:
    OpInfoBySymbol bySymbol;
    OpInfoByOp byOp;
  };

  static const OpInfoMap opInfoMap;
}

namespace Calculator {

  BinaryMathOperator::Ptr BinaryMathOperator::create(Operation op) {
    return Ptr(new BinaryMathOperator(op));
  }

  BinaryMathOperator::~BinaryMathOperator() {
  }

  BinaryMathOperator::BinaryMathOperator(Operation operation)
    :op(operation)
  {
  }

  Result BinaryMathOperator::operator()(Stack& stack, StackOperator::Ptr ofThis) {
    Number::Ptr first;
    Number::Ptr second;
    StackIterator iter = stack.begin();
    iter >> first >> second;
    // Defer stack.popAfter() until after evaluation

    if(!first) {
      iter.addError(0, Error::NotANumber);
    }
    if(!second) {
      iter.addError(1, Error::NotANumber);
    }

    if(!iter) {
      return iter.getResult();
    }

    // Do the math
    float result = 0.0;
    const OpInfo* info = opInfoMap[op];
    if(nullptr == info) {
      // Internal error....  Not sure what to do.
      return Result({"Internal Error: Missing BinaryMathOperator."});
    }

    stack.popAfter(iter);
    Number::Ptr item = Number::create(info->getFunction()(first->getValue(), second->getValue()));
    (*item)(stack, item);

    return Result({Error::Ok});
  }

  BinaryMathCreator::~BinaryMathCreator() {
  }

  std::string BinaryMathCreator::getHelp() const {
    return "One op of: +-*/^ -- Replace the top and second items with top op second.\n\t^ is exponent.";
  }

  StackOperator::Ptr BinaryMathCreator::create(const std::string& str) {
    const OpInfo* info = opInfoMap[str];
    if(nullptr != info) {
      return BinaryMathOperator::create(info->getOp());
    } else {
      return StackOperator::Ptr();
    }
  }

} // namespace Calculator
