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

#include <memory>
#include <limits>

#include "Error.h"
#include "Stack.h"
#include "Number.h"
#include "Variable.h"
#include "VariableSet.h"
#include "StackManipulator.h"

using namespace Calculator;
#include "Helpers.h"

class StackManipulatorsTest : public CppUnit::TestFixture {
private:
  CPPUNIT_TEST_SUITE(StackManipulatorsTest);

  CPPUNIT_TEST(testPopOfZero); 
  CPPUNIT_TEST(testPopOfOne); 
  CPPUNIT_TEST(testPopOfTwo); 

  CPPUNIT_TEST(testDupOfZero); 
  CPPUNIT_TEST(testPopOfOne); 
  CPPUNIT_TEST(testPopOfTwo); 

  CPPUNIT_TEST(testSwapOfZero); 
  CPPUNIT_TEST(testSwapOfOne); 
  CPPUNIT_TEST(testSwapOfTwo); 
  CPPUNIT_TEST(testSwapOfThree);

  CPPUNIT_TEST(testReset);
  CPPUNIT_TEST(testPopAll);

  CPPUNIT_TEST_SUITE_END();

private:
  template<unsigned int inputLength, unsigned int expectedLength>
  void test(const float (&input)[inputLength], StackManipulator::Operation oper, const float (&expected)[expectedLength]) {
    Stack stack;
    push(stack, input);

    const unsigned int required = StackManipulator::Operation::SWAP == oper ? 2 : 1;

    StackOperator::Ptr op = StackManipulator::create(oper);
    const Result result =(*op)(stack, op);
    if(inputLength < required) {
      verifyMessagesFound(Result({0, Error::StackUnderflow}), result);
      CPPUNIT_ASSERT(inputLength == stack.getDepth());
      verify(stack, input);
    } else {
      verifyMessagesFound(Result({Error::Ok}), result);
      CPPUNIT_ASSERT(expectedLength == stack.getDepth());
      verify(stack, expected);
    }
  }

  void test(StackManipulator::Operation oper) {
    Stack stack;

    // Disabled as unused; however, this likely needs to be tested as well
    // const unsigned int required = StackManipulator::Operation::SWAP == oper ? 2 : 1;

    StackOperator::Ptr op = StackManipulator::create(oper);
    const Result result =(*op)(stack, op);

    verifyMessagesFound(Result({{0, Error::StackUnderflow}}), result);
    CPPUNIT_ASSERT(stack.getDepth() == 0);
  }

public:
  void testPopOfZero() {
    test(StackManipulator::Operation::POP);
  }

  void testPopOfOne() {
    float input[] = { 1.0 };
    
    Stack stack;
    push(stack, input);

    StackOperator::Ptr op = StackManipulator::create(StackManipulator::Operation::POP);
    const Result result =(*op)(stack, op);
    
    verifyMessagesFound(Result({Error::Ok}), result);
    verify(stack);
  }

  void testPopOfTwo() {
    float input[] = { 1.0, 2.0 };
    float expected[] = { 1.0 };
    test(input, StackManipulator::Operation::POP, expected);
  }

  void testDupOfZero() {
    test(StackManipulator::Operation::DUP);
  }

  void testDupOfOne() {
    float input[] = { 1.0 };
    float expected[] = { 1.0, 1.0 };
    test(input, StackManipulator::Operation::DUP, expected);
  }

  void testDupOfTwo() {
    float input[] = { 1.0, 2.0 };
    float expected[] = { 1.0, 2.0, 2.0 };
    test(input, StackManipulator::Operation::DUP, expected);
  }

  void testSwapOfZero() {
    test(StackManipulator::Operation::SWAP);
  }

  void testSwapOfOne() {
    float input[] = { 1.0 };

    Stack stack;
    push(stack, input);

    StackOperator::Ptr op = StackManipulator::create(StackManipulator::Operation::SWAP);
    const Result result =(*op)(stack, op);

    verifyMessagesFound(Result({{1, Error::StackUnderflow}}), result);
    verify(stack, input);
  }

  void testSwapOfTwo() {
    float input[] = { 1.0, 2.0 };
    float expected[] = { 2.0, 1.0 };
    test(input, StackManipulator::Operation::SWAP, expected);
  }

  void testSwapOfThree() {
    float input[] = { 1.0, 2.0, 3.0 };
    float expected[] = { 1.0, 3.0, 2.0 };
    test(input, StackManipulator::Operation::SWAP, expected);
  }

  void testReset() {
    const float num = 3.14;
    Number::Ptr val = Number::create(num);
    Variable::Ptr foo = Variable::create("$foo");
    Variable::Ptr bar = Variable::create("$bar");

    Stack stack;
    stack.getVariables().set(bar->getName(), foo);
    stack.getVariables().set(foo->getName(), val);

    (*val)(stack, val);
    (*val)(stack, val);
    (*val)(stack, val);

    float expected[] = { num, num, num };
    verify(stack, expected);

    StackManipulator::Ptr op = StackManipulator::create(StackManipulator::Operation::RESET);
    (*op)(stack, val);

    verify(stack);

    StackItem::Ptr fooCheck = stack.getVariables().get(foo->getName());
    StackItem::Ptr barCheck = stack.getVariables().get(bar->getName());

    CPPUNIT_ASSERT(!fooCheck);
    CPPUNIT_ASSERT(!barCheck);
  }

  void testPopAll() {
    const float num = 3.14;
    Number::Ptr val = Number::create(num);
    Variable::Ptr foo = Variable::create("$foo");
    Variable::Ptr bar = Variable::create("$bar");

    Stack stack;
    stack.getVariables().set(bar->getName(), foo);
    stack.getVariables().set(foo->getName(), val);

    (*val)(stack, val);
    (*val)(stack, val);
    (*val)(stack, val);

    float expected[] = { num, num, num };
    verify(stack, expected);

    StackManipulator::Ptr op = StackManipulator::create(StackManipulator::Operation::POP_ALL);
    (*op)(stack, val);

    verify(stack);

    StackItem::Ptr fooCheck = stack.getVariables().get(foo->getName());
    StackItem::Ptr barCheck = stack.getVariables().get(bar->getName());

    CPPUNIT_ASSERT(fooCheck);
    CPPUNIT_ASSERT(fooCheck.get() == val.get());
    CPPUNIT_ASSERT(barCheck);
    CPPUNIT_ASSERT(barCheck.get() == foo.get());
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(StackManipulatorsTest);
