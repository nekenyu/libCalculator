#include <memory>
#include <vector>
#include <string>
#include <map>
#include <initializer_list>

#include "math.h"

#include "Error.h"
#include "BinaryMathOperator.h"
#include "Number.h"
#include "Stack.h"

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

  BinaryMathOperator::~BinaryMathOperator() {
  }

  BinaryMathOperator::BinaryMathOperator(Operation operation)
    :op(operation)
  {
  }
  
  std::string BinaryMathOperator::operator()(Stack& stack, StackOperator::Ptr ofThis) {
    if(stack.getDepth() < 2) {
      return Error::StackUnderflow;
    }

    StackItem::Ptr first;
    StackItem::Ptr second;
    StackIterator iter = stack.begin();
    iter >> first >> second;
    stack.popAfter(iter);

    // Do the math
    float result = 0.0;
    const OpInfo* info = opInfoMap[op];
    if(nullptr != info) {
      stack.push(StackItem::Ptr(new Number((info->getFunction()(first->getValue(), second->getValue())))));
      return Error::Ok;
    } else {
      // Internal error....  Not sure what to do.
      second->operator()(stack, second);
      first->operator()(stack, first);
      return "Internal Error: Missing BinaryMathOperator.";
    }
  }

  BinaryMathCreator::~BinaryMathCreator() {
  }

  std::string BinaryMathCreator::getHelp() const {
    return "One op of: +-*/^ -- Replace the top and second items with top op second.\n\t^ is exponent.";
  }

  StackOperator::Ptr BinaryMathCreator::create(const std::string& str) {
    const OpInfo* info = opInfoMap[str];
    if(nullptr != info) {
      return StackOperator::Ptr(new BinaryMathOperator(info->getOp()));
    } else {
      return StackOperator::Ptr();
    }
  }

} // namespace Calculator
