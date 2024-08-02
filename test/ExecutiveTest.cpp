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
#include <sstream>
#include <limits>
#include <iostream>

#include "Stack.h"
#include "Executive.h"
#include "Number.h"
#include "Variable.h"
#include "VariableSet.h"
#include "BinaryMathOperator.h"
#include "StackManipulator.h"
#include "VariableManipulator.h"
#include "StackOperatorFactory.h"

#include "Helpers.h"

#include "gtest/gtest.h"

using namespace Calculator;

class ExecutiveTest : public testing::Test {
protected:
  ExecutiveTest() {
    defaultFactory.addCreator(StackOperatorCreator::Ptr(new NumberCreator()));
    defaultFactory.addCreator(StackOperatorCreator::Ptr(new BinaryMathCreator()));
    defaultFactory.addCreator(StackOperatorCreator::Ptr(new StackManipulatorCreator()));
    defaultFactory.addCreator(StackOperatorCreator::Ptr(new VariableManipulatorCreator()));
    defaultFactory.addCreator(StackOperatorCreator::Ptr(new VariableCreator()));
  }
  // All other constructors, destructors, assignment operators = default;

  StackOperatorFactory defaultFactory;
};

void helpAllAVariables(Stack& stack) {
  StackItem::Ptr foo = stack.getVariables().get("$foo");
  StackItem::Ptr bar = stack.getVariables().get("$bar");
  EXPECT_NE(foo, nullptr);
  EXPECT_NE(bar, nullptr);

  Number::Ptr fooAsNum = std::dynamic_pointer_cast<Number, StackItem>(foo);
  Variable::Ptr barAsVar = std::dynamic_pointer_cast<Variable, StackItem>(bar);
  EXPECT_NE(fooAsNum, nullptr);
  EXPECT_NE(barAsVar, nullptr);

  const float fooAsFloat = fooAsNum->getValue();
  EXPECT_LT(abs(fooAsFloat - 2.5), (2 * std::numeric_limits<float>::epsilon()));

  EXPECT_EQ(barAsVar->getName().compare("$foo"), 0);
}

TEST_F(ExecutiveTest, AllA) {
  Stack stack;
  FixedOperatorExecutive f(defaultFactory, stack);
  
  {
    const std::string input = "5.0 -10.0 2.5 $foo dup $bar ! ! $bar * / ";
    std::istringstream is(input);
    std::ostringstream os;
    f.process(is, os);
    
    const float expected[] = { -5.0 };
    verify(stack, expected);
    helpAllAVariables(stack);
  }
  
  {
    const std::string input = "-0.1 - .1 + 2 swap ^ $bar @ pop invalid-token $bar @";
    std::istringstream is(input);
    std::ostringstream os;
    
    f.process(is, os);
    const float expected[] = { 25.0, 2.5 };
    verify(stack, expected);
    helpAllAVariables(stack);
  }
}
