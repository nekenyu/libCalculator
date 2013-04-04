#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <memory>
#include <limits>

// DO NOT COMMIT
#include <iostream>
using std::cout;
using std::endl;

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
