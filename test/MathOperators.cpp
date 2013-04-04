#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <memory>
#include <limits>

#include "Error.h"
#include "Stack.h"
#include "Number.h"
#include "BinaryMathOperator.h"

using namespace Calculator;
#include "Helpers.h"

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
  template<unsigned int inputLength, unsigned int expectedLength>
  void test(const float (&input)[inputLength], BinaryMathOperator::Operation oper, const float (&expected)[expectedLength]) {
    Stack stack;
    push(stack, input);

    StackOperator::Ptr op = BinaryMathOperator::create(oper);
    const std::string result = (*op)(stack, op);
    if(inputLength < 2) {
      CPPUNIT_ASSERT(0 == Error::StackUnderflow.compare(result));
      CPPUNIT_ASSERT(inputLength == stack.getDepth());
      verify(stack, input);
    } else {
      CPPUNIT_ASSERT(0 == Error::Ok.compare(result));
      CPPUNIT_ASSERT(expectedLength == stack.getDepth());
      verify(stack, expected);
    }
  }

  template<unsigned int inputLength>
  void test(const float (&input)[inputLength], BinaryMathOperator::Operation oper) {
    Stack stack;
    push(stack, input);

    StackOperator::Ptr op = BinaryMathOperator::create(oper);
    const std::string result = (*op)(stack, op);

    CPPUNIT_ASSERT(0 == Error::StackUnderflow.compare(result));
    CPPUNIT_ASSERT(inputLength == stack.getDepth());
    verify(stack, input);
  }

  void test(BinaryMathOperator::Operation oper) {
    Stack stack;

    StackOperator::Ptr op = BinaryMathOperator::create(oper);
    const std::string result = (*op)(stack, op);

    CPPUNIT_ASSERT(0 == Error::StackUnderflow.compare(result));
    CPPUNIT_ASSERT(stack.getDepth() == 0);
  }

public:
  void testAddOfZero() {
    test(BinaryMathOperator::Operation::ADD);
  }

  void testAddOfOne() {
    float input[] = { 1.0 };
    test(input, BinaryMathOperator::Operation::ADD);
  }

  void testAddOfTwo() {
    float input[] = { 1.0, 2.0 };
    float expected[] = { 3.0 };
    test(input, BinaryMathOperator::Operation::ADD, expected);
  }

  void testAddOfThree() {
    float input[] = { 0.0, 1.0, 2.0 };
    float expected[] = { 0.0, 3.0 };
    test(input, BinaryMathOperator::Operation::ADD, expected);
  }

  void testSubtractOfThree() {
    float input[] = { 0.0, 1.0, 2.0 };
    float expected[] = { 0.0, 1.0 };
    test(input, BinaryMathOperator::Operation::SUBTRACT, expected);
  }

  void testMultiplyOfThree() {
    float input[] = { 0.0, 1.0, 2.0 };
    float expected[] = { 0.0, 2.0 };
    test(input, BinaryMathOperator::Operation::MULTIPLY, expected);
  }

  void testDivideOfThree() {
    float input[] = { 0.0, 2.0, 1.0 };
    float expected[] = { 0.0, 0.5 };
    test(input, BinaryMathOperator::Operation::DIVIDE, expected);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MathOperatorsTest);
