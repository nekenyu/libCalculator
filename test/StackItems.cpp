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
#include "StackOperatorFactory.h"

#include "gtest/gtest.h"
using namespace Calculator;

void testNumberCreatorInvalid(const std::string& input) {
  NumberCreator numberCreator;
  StackOperator::Ptr created = numberCreator.create(input);
  EXPECT_EQ(created, nullptr);
}

void verify(StackOperator::Ptr created, const float expected) {
  EXPECT_NE(created, nullptr);
    
  Number::Ptr asStackItem = std::dynamic_pointer_cast<Number, StackOperator>(created);
  EXPECT_NE(asStackItem, nullptr);
  
  EXPECT_LT(abs(asStackItem->getValue() - expected), 2 * std::numeric_limits<float>::epsilon());
}

void testNumberCreatorValid(const std::string& input, const float expected) {
  NumberCreator numberCreator;
  {
    StackOperator::Ptr created = numberCreator.create(input);
    verify(created, expected);
  }

  {
    StackOperatorFactory factory;
    factory.addCreator(StackOperatorCreator::Ptr(new NumberCreator));
    StackOperator::Ptr created = factory.create(input);
    verify(created, expected);
  }
}

TEST(StackItemsTest, InvalidEmptyString) {
  testNumberCreatorInvalid("");
}

TEST(StackItemsTest, InvalidAlpha) {
  testNumberCreatorInvalid("x");
}

TEST(StackItemsTest, InvalidAlphaNumber) {
  testNumberCreatorInvalid("x5");
}

TEST(StackItemsTest, InvalidNumberAlpha) {
  testNumberCreatorInvalid("5x");
}

TEST(StackItemsTest, ValidIntZero) {
  testNumberCreatorValid("0", 0.0);
}

TEST(StackItemsTest, ValidFloatZero) {
  testNumberCreatorValid("0.0", 0.0);
}

TEST(StackItemsTest, ValidFloatTiny) {
  testNumberCreatorValid("0.00000001", 0.00000001);
}

TEST(StackItemsTest, ValidNegFloatTiny) {
  testNumberCreatorValid("-0.00000001", -0.00000001);
}

TEST(StackItemsTest, ValidFloatBig) {
  testNumberCreatorValid("987654321.987654321", 987654321.987654321);
}

TEST(StackItemsTest, ValidNegFloatBig) {
  testNumberCreatorValid("-987654321.987654321", -987654321.987654321);
}

TEST(StackItemsTest, InFactory) {
    NumberCreator numberCreator;
}