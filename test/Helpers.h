/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef HELPERS_H
#define HELPERS_H

#include "Stack.h"

#include "gtest/gtest.h"

/** Verify every message and positionMessage in expected is in found; however,
 * it is not required that every in found be in expected.
 *
 * @param expected Result data to look for
 * @param found Result info actually received
 */
inline void verifyMessagesFound(const Calculator::Result& expected, const Calculator::Result& found) {
  for(auto message : expected.getMessages()) {
    const bool hasMessage = found.hasMessage(message);
    EXPECT_TRUE(hasMessage) << "for: " << message;
  }

  for(auto positionMessage : expected.getPositionMessages()) {
    const bool hasPositionMessage = found.hasPositionMessage(positionMessage.first, positionMessage.second);
    if(!hasPositionMessage) {
      std::string str = std::to_string(positionMessage.first);
      str += ": ";
      str += positionMessage.second;
      
      FAIL() << str;
    }
  }
}

/** Push value as a Number onto stack
 * 
 * @param stack to push onto
 * @param value to push as number
 */
inline void push(Calculator::Stack& stack, float value) {
  stack.push(Calculator::Number::create(value));
}

/** Push all of input onto stack
 *
 * @tparam inputLength length of input array to push
 * @param stack to push onto
 * @param input array of values to push
 */
template<unsigned int inputLength>
  void push(Calculator::Stack& stack, const float (&input)[inputLength]) {
    for(unsigned int i = 0; i < inputLength; ++i) {
      push(stack, input[i]);
    }
  }

/** Verify stack is empty, that its depth is zero, that its iterators are equal
 *
 * @param stack to test
 */
inline void verify(Calculator::Stack& stack) {
  EXPECT_EQ(stack.getDepth(), static_cast<Calculator::Stack::Count>(0));
  EXPECT_EQ(stack.end(), stack.begin());
}

/** Verify stack contains precisely the getValue()s and length of expected
 *
 * @tparam length of expected to check and depth of Stack
 * @param stack to test
 * @param expected the values expected in the Stack with expected[0] being
 * bottom-most and expected[length - 1] being the top
 *
 * \note Failure to verify fails the test case.
 */
template<unsigned int length>
void verify(Calculator::Stack& stack, const float(&expected)[length]) {
  EXPECT_EQ(length, stack.getDepth());
  
  Calculator::StackIterator iter = stack.begin();
  for(unsigned int i = 0; i < length; ++i, ++iter) {
    Calculator::Number::Ptr value = iter.as<Calculator::Number>();
    EXPECT_NE(value, nullptr);
    EXPECT_LT(abs(expected[length - 1 - i] - value->getValue()), 2 * std::numeric_limits<float>::epsilon());
  }

  EXPECT_EQ(stack.end(), iter);
}

#endif // HELPERS_H
