/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <memory>
#include <sstream>
#include <limits>
#include <iostream>

#include "Stack.h"
#include "Executive.h"
#include "Number.h"
#include "Variable.h"
#include "BinaryMathOperator.h"
#include "StackManipulator.h"
#include "VariableManipulator.h"
#include "StackOperatorFactory.h"

using namespace Calculator;

#include "Helpers.h"

class ExecutiveTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(ExecutiveTest);

  CPPUNIT_TEST(testAllA);
  CPPUNIT_TEST_SUITE_END();

public:

ExecutiveTest() {
  defaultFactory.addCreator(StackOperatorCreator::Ptr(new NumberCreator()));
  defaultFactory.addCreator(StackOperatorCreator::Ptr(new BinaryMathCreator()));
  defaultFactory.addCreator(StackOperatorCreator::Ptr(new StackManipulatorCreator()));
  defaultFactory.addCreator(StackOperatorCreator::Ptr(new VariableManipulatorCreator()));
  defaultFactory.addCreator(StackOperatorCreator::Ptr(new VariableCreator()));
}

public:

void testAllA() {
Stack stack;
FixedOperatorExecutive f(defaultFactory, stack);

{
const std::string input = "5.0 -10.0 2.5 $foo dup $bar ! ! $bar * / ";
std::istringstream is(input);
std::ostringstream os;
f.process(is, os);

const float expected[] = { -5.0 };
verify(stack, expected);
/** \todo Consider verifying variables */
}

{
const std::string input = "-0.1 - .1 + 2 swap ^ $bar @ pop invalid-token $bar @";
std::istringstream is(input);
std::ostringstream os;

f.process(is, os);
const float expected[] = { 25.0, 2.5 };
verify(stack, expected);
/** \todo Consider verifying variables */
}
}

private:
StackOperatorFactory defaultFactory;
};

CPPUNIT_TEST_SUITE_REGISTRATION(ExecutiveTest);
