#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <memory>
#include <limits>

#include "Error.h"
#include "Stack.h"
#include "Number.h"
#include "BinaryMathOperator.h"

using namespace Calculator;

class MathOperatorsTest : public CppUnit::TestFixture {
private:
  CPPUNIT_TEST_SUITE(MathOperatorsTest);

  CPPUNIT_TEST(testAddOfZero);
  CPPUNIT_TEST(testAddOfOne);
  CPPUNIT_TEST(testAddOfTwo);
  CPPUNIT_TEST(testAddOfThree);

  CPPUNIT_TEST(testSubtractOfThree);
  CPPUNIT_TEST(testMultiplyOfThree);
  CPPUNIT_TEST(testDivideOfThree);

  CPPUNIT_TEST_SUITE_END();

private:
  void push(Stack& stack, float value) {
    stack.push(StackItem::Ptr(new Number(value)));
  }

  void destructiveVerify(Stack& stack, const float* const expected, const size_t expectedLength) {
    StackItem::Ptr values[expectedLength];
    const bool popped = stack.pop(expectedLength, values);
    CPPUNIT_ASSERT(popped);
    CPPUNIT_ASSERT(0 == stack.getDepth());

    // Compare expected to values in opposite order...  pop() buts top first
    // while test results put top to the right.
    for(int i = 0; i < expectedLength; ++i) {
      CPPUNIT_ASSERT(abs(expected[i] - values[expectedLength - 1 -i]->getValue()) < 2 * std::numeric_limits<float>::epsilon());
    }
  }

  void test(const float* const input, const size_t inputLength, BinaryMathOperator::Operation oper, const float* const expected, const size_t expectedLength) {
    Stack stack;
    for(int i = 0; i < inputLength; ++i) {
      push(stack, input[i]);
    }

    StackOperator::Ptr op(new BinaryMathOperator(oper));
    const std::string result = (*op)(stack, op);
    if(inputLength < 2) {
      CPPUNIT_ASSERT(0 == Error::StackUnderflow.compare(result));
      CPPUNIT_ASSERT(inputLength == stack.getDepth());
      destructiveVerify(stack, input, inputLength);
    } else {
      CPPUNIT_ASSERT(0 == Error::Ok.compare(result));
      CPPUNIT_ASSERT(expectedLength == stack.getDepth());
      destructiveVerify(stack, expected, expectedLength);
    }
  }

public:
  void testAddOfZero() {
    test(NULL, 0, BinaryMathOperator::Operation::ADD, NULL, 0);
  }

  void testAddOfOne() {
    float input[] = { 1.0 };
    test(input, sizeof(input)/sizeof(float), BinaryMathOperator::Operation::ADD, NULL, 0);
  }

  void testAddOfTwo() {
    float input[] = { 1.0, 2.0 };
    float expected[] = { 3.0 };
    test(input, sizeof(input)/sizeof(float), BinaryMathOperator::Operation::ADD, expected, sizeof(expected)/sizeof(float));
  }

  void testAddOfThree() {
    float input[] = { 0.0, 1.0, 2.0 };
    float expected[] = { 0.0, 3.0 };
    test(input, sizeof(input)/sizeof(float), BinaryMathOperator::Operation::ADD, expected, sizeof(expected)/sizeof(float));
  }

  void testSubtractOfThree() {
    float input[] = { 0.0, 1.0, 2.0 };
    float expected[] = { 0.0, 1.0 };
    test(input, sizeof(input)/sizeof(float), BinaryMathOperator::Operation::SUBTRACT, expected, sizeof(expected)/sizeof(float));
  }

  void testMultiplyOfThree() {
    float input[] = { 0.0, 1.0, 2.0 };
    float expected[] = { 0.0, 2.0 };
    test(input, sizeof(input)/sizeof(float), BinaryMathOperator::Operation::MULTIPLY, expected, sizeof(expected)/sizeof(float));
  }

  void testDivideOfThree() {
    float input[] = { 0.0, 2.0, 1.0 };
    float expected[] = { 0.0, 0.5 };
    test(input, sizeof(input)/sizeof(float), BinaryMathOperator::Operation::DIVIDE, expected, sizeof(expected)/sizeof(float));
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MathOperatorsTest);
