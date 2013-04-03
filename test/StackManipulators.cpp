#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <memory>
#include <limits>

#include "Error.h"
#include "Stack.h"
#include "Number.h"
#include "StackManipulator.h"

using namespace Calculator;

class MathOperatorsTest : public CppUnit::TestFixture {
private:
  CPPUNIT_TEST_SUITE(MathOperatorsTest);

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

  void test(const float* const input, const size_t inputLength, StackManipulator::Operation oper, const float* const expected, const size_t expectedLength) {
    Stack stack;
    for(int i = 0; i < inputLength; ++i) {
      push(stack, input[i]);
    }
    const unsigned int required = StackManipulator::Operation::SWAP == oper ? 2 : 1;

    StackOperator::Ptr op(new StackManipulator(oper));
    const std::string result = (*op)(stack, op);
    if(inputLength < required) {
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
  void testPopOfZero() {
    test(NULL, 0, StackManipulator::Operation::POP, NULL, 0);
  }

  void testPopOfOne() {
    float input[] = { 1.0 };
    test(input, sizeof(input)/sizeof(float), StackManipulator::Operation::POP, NULL, 0);
  }

  void testPopOfTwo() {
    float input[] = { 1.0, 2.0 };
    float expected[] = { 1.0 };
    test(input, sizeof(input)/sizeof(float), StackManipulator::Operation::POP, expected, sizeof(expected)/sizeof(float));
  }

  void testDupOfZero() {
    test(NULL, 0, StackManipulator::Operation::DUP, NULL, 0);
  }

  void testDupOfOne() {
    float input[] = { 1.0 };
    float expected[] = { 1.0, 1.0 };
    test(input, sizeof(input)/sizeof(float), StackManipulator::Operation::DUP, NULL, 0);
  }

  void testDupOfTwo() {
    float input[] = { 1.0, 2.0 };
    float expected[] = { 1.0, 2.0, 2.0 };
    test(input, sizeof(input)/sizeof(float), StackManipulator::Operation::DUP, expected, sizeof(expected)/sizeof(float));
  }

  void testSwapOfZero() {
    test(NULL, 0, StackManipulator::Operation::SWAP, NULL, 0);
  }

  void testSwapOfOne() {
    float input[] = { 1.0 };
    test(input, sizeof(input)/sizeof(float), StackManipulator::Operation::SWAP, NULL, 0);
  }

  void testSwapOfTwo() {
    float input[] = { 1.0, 2.0 };
    float expected[] = { 2.0, 1.0 };
    test(input, sizeof(input)/sizeof(float), StackManipulator::Operation::DUP, expected, sizeof(expected)/sizeof(float));
  }

  void testSwapOfThree() {
    float input[] = { 1.0, 2.0, 3.0 };
    float expected[] = { 1.0, 3.0, 2.0 };
    test(input, sizeof(input)/sizeof(float), StackManipulator::Operation::DUP, expected, sizeof(expected)/sizeof(float));
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MathOperatorsTest);
