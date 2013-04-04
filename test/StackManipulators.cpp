#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <memory>
#include <limits>

#include "Error.h"
#include "Stack.h"
#include "Number.h"
#include "StackManipulator.h"

using namespace Calculator;
#include "Helpers.h"

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
  template<unsigned int inputLength, unsigned int expectedLength>
  void test(const float (&input)[inputLength], StackManipulator::Operation oper, const float (&expected)[expectedLength]) {
    Stack stack;
    push(stack, input);

    const unsigned int required = StackManipulator::Operation::SWAP == oper ? 2 : 1;

    StackOperator::Ptr op = StackManipulator::create(oper);
    const std::string result = (*op)(stack, op);
    if(inputLength < required) {
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
  void test(const float (&input)[inputLength], StackManipulator::Operation oper) {
    Stack stack;
    push(stack, input);

    const unsigned int required = StackManipulator::Operation::SWAP == oper ? 2 : 1;

    StackOperator::Ptr op = StackManipulator::create(oper);
    const std::string result = (*op)(stack, op);

    CPPUNIT_ASSERT(0 == Error::StackUnderflow.compare(result));
    CPPUNIT_ASSERT(inputLength == stack.getDepth());
    verify(stack, input);
  }

  void test(StackManipulator::Operation oper) {
    Stack stack;

    const unsigned int required = StackManipulator::Operation::SWAP == oper ? 2 : 1;

    StackOperator::Ptr op = StackManipulator::create(oper);
    const std::string result = (*op)(stack, op);

    CPPUNIT_ASSERT(0 == Error::StackUnderflow.compare(result));
    CPPUNIT_ASSERT(stack.getDepth() == 0);
  }

public:
  void testPopOfZero() {
    test(StackManipulator::Operation::POP);
  }

  void testPopOfOne() {
    float input[] = { 1.0 };
    test(input, StackManipulator::Operation::POP);
  }

  void testPopOfTwo() {
    float input[] = { 1.0, 2.0 };
    float expected[] = { 1.0 };
    test(input, StackManipulator::Operation::POP, expected);
  }

  void testDupOfZero() {
    test(StackManipulator::Operation::DUP);
  }

  void testDupOfOne() {
    float input[] = { 1.0 };
    float expected[] = { 1.0, 1.0 };
    test(input, StackManipulator::Operation::DUP);
  }

  void testDupOfTwo() {
    float input[] = { 1.0, 2.0 };
    float expected[] = { 1.0, 2.0, 2.0 };
    test(input, StackManipulator::Operation::DUP, expected);
  }

  void testSwapOfZero() {
    test(StackManipulator::Operation::SWAP);
  }

  void testSwapOfOne() {
    float input[] = { 1.0 };
    test(input, StackManipulator::Operation::SWAP);
  }

  void testSwapOfTwo() {
    float input[] = { 1.0, 2.0 };
    float expected[] = { 2.0, 1.0 };
    test(input, StackManipulator::Operation::DUP, expected);
  }

  void testSwapOfThree() {
    float input[] = { 1.0, 2.0, 3.0 };
    float expected[] = { 1.0, 3.0, 2.0 };
    test(input, StackManipulator::Operation::DUP, expected);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MathOperatorsTest);
