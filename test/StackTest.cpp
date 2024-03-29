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

#include "Stack.h"
#include "Number.h"
#include "Variable.h"
#include "VariableSet.h"
#include "Error.h"

using namespace Calculator;

#include "Helpers.h"

class StackTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(StackTest);

  CPPUNIT_TEST(testEmpty);
  CPPUNIT_TEST(testPushOne);
  CPPUNIT_TEST(testPushFive);

  CPPUNIT_TEST(testPopAfterZeroOfZero);
  CPPUNIT_TEST(testPopAfterZeroOfOne);
  CPPUNIT_TEST(testPopAfterOneOfOne);
  CPPUNIT_TEST(testPopAfterOneOfTwo);
  CPPUNIT_TEST(testPopAfterTwoOfThree);

  CPPUNIT_TEST(testIterDereference);
  CPPUNIT_TEST(testIterGets);
  CPPUNIT_TEST(testIterAs);
  CPPUNIT_TEST(testIterGetsAs);

  CPPUNIT_TEST_SUITE_END();

public:
  void testEmpty() {
    Stack stack;
    verify(stack);
  }

  void testPushOne() {
    Stack stack;
    stack.push(Number::create(0.0));

    float input[] = { 0.0 };
    verify(stack, input);
  }

  void testPushFive() {
    Stack stack;
    stack.push(Number::create(0.0));
    stack.push(Number::create(2.0));
    stack.push(Number::create(3.0));
    stack.push(Number::create(4.0));
    stack.push(Number::create(5.0));

    float input[] = { 0.0, 2.0, 3.0, 4.0, 5.0 };
    verify(stack, input);
  }

  void testPopAfterZeroOfZero() {
    Stack stack;
    verify(stack);

    StackIterator iter = stack.begin();
    CPPUNIT_ASSERT(stack.end() == iter);
    
    stack.popAfter(iter);
    CPPUNIT_ASSERT(stack.end() == iter);
    verify(stack);
  }

  void testPopAfterZeroOfOne() {
    float input[] = { 1.0 };
    Stack stack;
    push(stack, input);

    verify(stack, input);

    StackIterator iter = stack.begin();
    stack.popAfter(iter);
    CPPUNIT_ASSERT(stack.begin() == iter);
    verify(stack, input);
  }

  void testPopAfterOneOfOne() {
    float input[] = { 1.0 };
    Stack stack;
    push(stack, input);
    verify(stack, input);

    StackIterator iter = stack.begin();
    ++iter;
    stack.popAfter(iter);
    CPPUNIT_ASSERT(stack.begin() == iter);
    verify(stack);
  }

  void testPopAfterOneOfTwo() {
    float input[] = { 1.0, 2.0 };
    Stack stack;
    push(stack, input);
    verify(stack, input);

    StackIterator iter = stack.begin();
    ++iter;
    stack.popAfter(iter);
    CPPUNIT_ASSERT(stack.begin() == iter);

    float expected[] = { 1.0 };
    verify(stack, expected);
  }

  void testPopAfterTwoOfThree() {
    float input[] = { 1.0, 2.0, 3.0 };
    Stack stack;
    push(stack, input);
    verify(stack, input);

    StackIterator iter = stack.begin();
    ++iter;
    stack.popAfter(iter);
    CPPUNIT_ASSERT(stack.begin() == iter);

    float expected[] = { 1.0, 2.0 };
    verify(stack, expected);
  }

  void testIterDereference() {
    Variable::Ptr variable = Variable::create("$test");
    Number::Ptr number = Number::create(1.2345);

    Stack stack;
    stack.getVariables().set(variable->getName(), number);
    stack.push(variable);

    float expected[] = { number->getValue() };
    verify(stack, expected);

    StackIterator iter = stack.begin();
    CPPUNIT_ASSERT(*iter == number);

    iter.setHint(StackIterator::Hint::NO_DEREFERENCE_NEXT);
    CPPUNIT_ASSERT(*iter == variable);
    CPPUNIT_ASSERT(*iter == number);

    iter.setHint(StackIterator::Hint::NO_DEREFERENCE_NEXT);
    iter.setHint(StackIterator::Hint::DEREFERENCE_NEXT);
    CPPUNIT_ASSERT(*iter == number);

    CPPUNIT_ASSERT(iter.noDereference() == variable);

    verify(stack, expected);
  }

  void testIterGets() {
    Variable::Ptr variable = Variable::create("$test");
    Number::Ptr number = Number::create(1.2345);

    Stack stack;
    stack.getVariables().set(variable->getName(), number);
    stack.push(variable);
    stack.push(variable);

    float expected[] = { number->getValue(), number->getValue() };
    verify(stack, expected);

    {
      StackIterator iter = stack.begin();
      StackItem::Ptr item;
      iter >> item;
      CPPUNIT_ASSERT(item == number);
    }

    {
      StackIterator iter = stack.begin();
      StackItem::Ptr item;
      iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> item;
      CPPUNIT_ASSERT(item == variable);
    }

    {
      StackIterator iter = stack.begin();
      StackItem::Ptr itemVariable;
      StackItem::Ptr itemNumber;
      iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> itemVariable >> itemNumber;
      CPPUNIT_ASSERT(itemVariable == variable);
      CPPUNIT_ASSERT(itemNumber == number);
    }

    {
      StackIterator iter = stack.begin();
      StackItem::Ptr item;
      iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> StackIterator::Hint::DEREFERENCE_NEXT >> item;
      CPPUNIT_ASSERT(item == number);
    }

    verify(stack, expected);
  }

  void testIterAs() {
    Variable::Ptr variable = Variable::create("$test");
    Number::Ptr number = Number::create(1.2345);

    Stack stack;
    stack.getVariables().set(variable->getName(), number);
    stack.push(variable);
    stack.push(variable);
    stack.push(variable);
    stack.push(variable);
    stack.push(variable);

    float expected[] = { number->getValue(), number->getValue(), number->getValue(), number->getValue(), number->getValue() };
    verify(stack, expected);

    StackIterator iter = stack.begin();
    CPPUNIT_ASSERT(stack.end() != iter);

    StackItem::Ptr item1 = *(iter++);
    CPPUNIT_ASSERT(item1);
    CPPUNIT_ASSERT(item1 == number);
    CPPUNIT_ASSERT(stack.end() != iter);

    Number::Ptr item2 = iter++.as<Number>();
    CPPUNIT_ASSERT(item2);
    CPPUNIT_ASSERT(item2 == number);
    CPPUNIT_ASSERT(stack.end() != iter);

    Variable::Ptr item3 = iter++.setHint(StackIterator::Hint::NO_DEREFERENCE_NEXT).as<Variable>();
    CPPUNIT_ASSERT(item3);
    CPPUNIT_ASSERT(item3 == variable);
    CPPUNIT_ASSERT(stack.end() != iter);

    Number::Ptr item4 = iter++.as<Number>();
    CPPUNIT_ASSERT(stack.end() != iter);
    CPPUNIT_ASSERT(item4);
    CPPUNIT_ASSERT(item4 == number);

    Number::Ptr item5 = iter++.as<Number>();
    CPPUNIT_ASSERT(stack.end() == iter);
    CPPUNIT_ASSERT(item5);
    CPPUNIT_ASSERT(item5 == number);

    verify(stack, expected);
  }

  void testIterGetsAs() {
    Variable::Ptr variable = Variable::create("$test");
    Number::Ptr number = Number::create(1.2345);

    Stack stack;
    stack.push(variable);
    stack.push(variable);
    stack.push(variable);
    stack.push(variable);
    stack.push(variable);
    stack.getVariables().set(variable->getName(), number);

    float expected[] = { number->getValue(), number->getValue(), number->getValue(), number->getValue(), number->getValue() };
    verify(stack, expected);

    StackItem::Ptr item1;
    Number::Ptr item2;
    Variable::Ptr item3;
    Number::Ptr item4;
    Number::Ptr item5;

    StackIterator iter = stack.begin();
    CPPUNIT_ASSERT(stack.end() != iter);
    iter >> item1
	 >> item2
	 >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> item3
	 >> item4
	 >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> StackIterator::Hint::DEREFERENCE_NEXT >> item5;
    CPPUNIT_ASSERT(stack.end() == iter);

    CPPUNIT_ASSERT(item1);
    CPPUNIT_ASSERT(item1 == number);

    CPPUNIT_ASSERT(item2);
    CPPUNIT_ASSERT(item2 == number);

    CPPUNIT_ASSERT(item3);
    CPPUNIT_ASSERT(item3 == variable);

    CPPUNIT_ASSERT(item4);
    CPPUNIT_ASSERT(item4 == number);

    CPPUNIT_ASSERT(item5);
    CPPUNIT_ASSERT(item5 == number);

    verify(stack, expected);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(StackTest);
