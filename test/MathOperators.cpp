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

#include "Error.h"
#include "Stack.h"
#include "Number.h"
#include "BinaryMathOperator.h"

#include "Helpers.h"

#include "gtest/gtest.h"

using namespace Calculator;

template<unsigned int inputLength, unsigned int expectedLength>
void test(const float (&input)[inputLength], BinaryMathOperator::Operation oper, const float (&expected)[expectedLength]) {
  Stack stack;
  push(stack, input);

  StackOperator::Ptr op = BinaryMathOperator::create(oper);
  const Result result = (*op)(stack, op);
  if(inputLength < 2) {
    verifyMessagesFound(Result({{0, Error::StackUnderflow}}), result);
    EXPECT_EQ(inputLength, stack.getDepth());
    verify(stack, input);
  } else {
    verifyMessagesFound(Result({Error::Ok}), result);
    EXPECT_EQ(expectedLength, stack.getDepth());
    verify(stack, expected);
  }
}

template<unsigned int inputLength>
void test(const float (&input)[inputLength], BinaryMathOperator::Operation oper) {
  Stack stack;
  push(stack, input);

  StackOperator::Ptr op = BinaryMathOperator::create(oper);
  const Result result = (*op)(stack, op);

  verifyMessagesFound(Result({{1, Error::StackUnderflow}}), result);
  EXPECT_EQ(inputLength, stack.getDepth());
  verify(stack, input);
}

void test(BinaryMathOperator::Operation oper) {
  Stack stack;

  StackOperator::Ptr op = BinaryMathOperator::create(oper);
  const Result result = (*op)(stack, op);

  verifyMessagesFound(Result({{0, Error::StackUnderflow}, {1, Error::StackUnderflow}}), result);
  EXPECT_EQ(stack.getDepth(), static_cast<Calculator::Stack::Count>(0));
}

TEST(MathOperatorsTest, AddOfZero) {
  test(BinaryMathOperator::Operation::ADD);
}

TEST(MathOperatorsTest, AddOfOne) {
  float input[] = { 1.0 };
  test(input, BinaryMathOperator::Operation::ADD);
}

TEST(MathOperatorsTest, AddOfTwo) {
  float input[] = { 1.0, 2.0 };
  float expected[] = { 3.0 };
  test(input, BinaryMathOperator::Operation::ADD, expected);
}

TEST(MathOperatorsTest, AddOfThree) {
  float input[] = { 0.0, 1.0, 2.0 };
  float expected[] = { 0.0, 3.0 };
  test(input, BinaryMathOperator::Operation::ADD, expected);
}

TEST(MathOperatorsTest, SubtractOfThree) {
  float input[] = { 0.0, 1.0, 2.0 };
  float expected[] = { 0.0, 1.0 };
  test(input, BinaryMathOperator::Operation::SUBTRACT, expected);
}

TEST(MathOperatorsTest, MultiplyOfThree) {
  float input[] = { 0.0, 1.0, 2.0 };
  float expected[] = { 0.0, 2.0 };
  test(input, BinaryMathOperator::Operation::MULTIPLY, expected);
}

TEST(MathOperatorsTest, DivideOfThree) {
  float input[] = { 0.0, 2.0, 1.0 };
  float expected[] = { 0.0, 0.5 };
  test(input, BinaryMathOperator::Operation::DIVIDE, expected);
}