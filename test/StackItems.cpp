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
#include <limits>

#include "Error.h"
#include "Stack.h"
#include "Number.h"
#include "BinaryMathOperator.h"
#include "StackOperatorFactory.h"

using namespace Calculator;

class StackItemsTest : public CppUnit::TestFixture {
private:
  CPPUNIT_TEST_SUITE(StackItemsTest);

  CPPUNIT_TEST(testNumberCreatorBlank);
  CPPUNIT_TEST(testNumberCreatorNon);
  CPPUNIT_TEST(testNumberCreatorNonNumber);
  CPPUNIT_TEST(testNumberCreatorNumberNon);
  CPPUNIT_TEST(testNumberCreatorIntZero);
  CPPUNIT_TEST(testNumberCreatorFloatZero);

  CPPUNIT_TEST(testNumberCreatorFloatTiny);
  CPPUNIT_TEST(testNumberCreatorFloatNegTiny);
  CPPUNIT_TEST(testNumberCreatorFloatBig);
  CPPUNIT_TEST(testNumberCreatorFloatNegBig);

  CPPUNIT_TEST_SUITE_END();

private:
  void testNumberCreatorInvalid(const std::string& input) {
    StackOperator::Ptr created = numberCreator.create(input);
    CPPUNIT_ASSERT(!created);
  }

  void verify(StackOperator::Ptr created, const float expected) {
      CPPUNIT_ASSERT(created);
      
      Number::Ptr asStackItem = std::dynamic_pointer_cast<Number, StackOperator>(created);
      CPPUNIT_ASSERT(asStackItem);
      
      CPPUNIT_ASSERT(abs(asStackItem->getValue() - expected) < 2 * std::numeric_limits<float>::epsilon());
  }

  void testNumberCreatorValid(const std::string& input, const float expected) {
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

public:
  void testNumberCreatorBlank() {
    testNumberCreatorInvalid("");
  }

  void testNumberCreatorNon() {
    testNumberCreatorInvalid("x");
  }

  void testNumberCreatorNonNumber() {
    testNumberCreatorInvalid("x5");
  }

  void testNumberCreatorNumberNon() {
    testNumberCreatorInvalid("5x");
  }

  void testNumberCreatorIntZero() {
    testNumberCreatorValid("0", 0.0);
  }

  void testNumberCreatorFloatZero() {
    testNumberCreatorValid("0.0", 0.0);
  }

  void testNumberCreatorFloatTiny() {
    testNumberCreatorValid("0.00000001", 0.00000001);
  }

  void testNumberCreatorFloatNegTiny() {
    testNumberCreatorValid("-0.00000001", -0.00000001);
  }

  void testNumberCreatorFloatBig() {
    testNumberCreatorValid("987654321.987654321", 987654321.987654321);
  }

  void testNumberCreatorFloatNegBig() {
    testNumberCreatorValid("-987654321.987654321", -987654321.987654321);
  }

  void testNumberCreatorInFactory() {

  }

private:
  NumberCreator numberCreator;
};

CPPUNIT_TEST_SUITE_REGISTRATION(StackItemsTest);
