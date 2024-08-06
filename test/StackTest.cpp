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
#include <limits>

#include "Stack.h"
#include "Number.h"
#include "Variable.h"
#include "VariableSet.h"
#include "Error.h"

#include "Helpers.h"

#include "gtest/gtest.h"

using namespace Calculator;

TEST(StackTest, Empty) {
  Stack stack;
  verify(stack);
}

TEST(StackTest, PushOne) {
  Stack stack;
  stack.push(Number::create(0.0));

  float input[] = { 0.0 };
  verify(stack, input);
}

TEST(StackTest, PushFive) {
  Stack stack;
  stack.push(Number::create(0.0));
  stack.push(Number::create(2.0));
  stack.push(Number::create(3.0));
  stack.push(Number::create(4.0));
  stack.push(Number::create(5.0));

  float input[] = { 0.0, 2.0, 3.0, 4.0, 5.0 };
  verify(stack, input);
}

TEST(StackTest, PopAfterZeroOfZero) {
  Stack stack;
  verify(stack);

  // Ensure Empty
  StackIterator iter = stack.begin();
  EXPECT_EQ(stack.end(),  iter);

  stack.popAfter(iter);
  EXPECT_EQ(stack.end(), iter);
  verify(stack);
}

TEST(StackTest, PopAfterZeroOfOne) {
  float input[] = { 1.0 };
  Stack stack;
  push(stack, input);

  verify(stack, input);

  StackIterator iter = stack.begin();
  stack.popAfter(iter);
  EXPECT_EQ(stack.begin(), iter);
  verify(stack, input);
}

TEST(StackTest, PopAfterOneOfOne) {
  float input[] = { 1.0 };
  Stack stack;
  push(stack, input);
  verify(stack, input);

  StackIterator iter = stack.begin();
  ++iter;
  stack.popAfter(iter);
  EXPECT_EQ(stack.begin(), iter);
  verify(stack);
}

TEST(StackTest, PopAfterOneOfTwo) {
  float input[] = { 1.0, 2.0 };
  Stack stack;
  push(stack, input);
  verify(stack, input);

  StackIterator iter = stack.begin();
  ++iter;
  stack.popAfter(iter);
  EXPECT_EQ(stack.begin(), iter);

  float expected[] = { 1.0 };
  verify(stack, expected);
}

TEST(StackTest, PopAfterTwoOfThree) {
  float input[] = { 1.0, 2.0, 3.0 };
  Stack stack;
  push(stack, input);
  verify(stack, input);

  StackIterator iter = stack.begin();
  ++iter;
  stack.popAfter(iter);
  EXPECT_EQ(stack.begin(), iter);

  float expected[] = { 1.0, 2.0 };
  verify(stack, expected);
}

TEST(StackTest, IterDereference) {
  Variable::Ptr variable = Variable::create("$test");
  Number::Ptr number = Number::create(1.2345);

  Stack stack;
  stack.getVariables().set(variable->getName(), number);
  stack.push(variable);

  float expected[] = { number->getValue() };
  verify(stack, expected);

  StackIterator iter = stack.begin();
  EXPECT_EQ(*iter, number);

  iter.setHint(StackIterator::Hint::NO_DEREFERENCE_NEXT);
  EXPECT_EQ(*iter, variable);
  EXPECT_EQ(*iter, number);

  iter.setHint(StackIterator::Hint::NO_DEREFERENCE_NEXT);
  iter.setHint(StackIterator::Hint::DEREFERENCE_NEXT);
  EXPECT_EQ(*iter, number);

  EXPECT_EQ(iter.noDereference(), variable);

  verify(stack, expected);
}

TEST(StackTest, IterGets) {
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
    EXPECT_EQ(item, number);
  }

  {
    StackIterator iter = stack.begin();
    StackItem::Ptr item;
    iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> item;
    EXPECT_EQ(item, variable);
  }

  {
    StackIterator iter = stack.begin();
    StackItem::Ptr itemVariable;
    StackItem::Ptr itemNumber;
    iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> itemVariable >> itemNumber;
    EXPECT_EQ(itemVariable, variable);
    EXPECT_EQ(itemNumber, number);
  }

  {
    StackIterator iter = stack.begin();
    StackItem::Ptr item;
    iter >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> StackIterator::Hint::DEREFERENCE_NEXT >> item;
    EXPECT_EQ(item, number);
  }

  verify(stack, expected);
}

TEST(StackTest, IterAs) {
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
  EXPECT_NE(stack.end(), iter);

  StackItem::Ptr item1 = *(iter++);
  EXPECT_NE(item1, nullptr);
  EXPECT_EQ(item1, number);
  EXPECT_NE(stack.end(), iter);

  Number::Ptr item2 = iter++.as<Number>();
  EXPECT_NE(item2, nullptr);
  EXPECT_EQ(item2, number);
  EXPECT_NE(stack.end(), iter);

  Variable::Ptr item3 = iter++.setHint(StackIterator::Hint::NO_DEREFERENCE_NEXT).as<Variable>();
  EXPECT_NE(item3, nullptr);
  EXPECT_EQ(item3, variable);
  EXPECT_NE(stack.end(), iter);

  Number::Ptr item4 = iter++.as<Number>();
  EXPECT_NE(stack.end(), iter);
  EXPECT_NE(item4, nullptr);
  EXPECT_EQ(item4, number);

  Number::Ptr item5 = iter++.as<Number>();
  EXPECT_EQ(stack.end(), iter);
  EXPECT_NE(item5, nullptr);
  EXPECT_EQ(item5, number);

  verify(stack, expected);
}

TEST(StackTest, IterGetsAs) {
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
  EXPECT_NE(stack.end(), iter);
  iter >> item1
  >> item2
  >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> item3
  >> item4
  >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> StackIterator::Hint::DEREFERENCE_NEXT >> item5;
  EXPECT_EQ(stack.end(), iter);

  EXPECT_NE(item1, nullptr);
  EXPECT_EQ(item1, number);

  EXPECT_NE(item2, nullptr);
  EXPECT_EQ(item2, number);

  EXPECT_NE(item3, nullptr);
  EXPECT_EQ(item3, variable);

  EXPECT_NE(item4, nullptr);
  EXPECT_EQ(item4, number);

  EXPECT_NE(item5, nullptr);
  EXPECT_EQ(item5, number);

  verify(stack, expected);
}