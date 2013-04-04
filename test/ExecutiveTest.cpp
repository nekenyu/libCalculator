#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <memory>
#include <sstream>
#include <limits>
#include <iostream>

#include "Stack.h"
#include "Executive.h"
#include "Number.h"
#include "Variable.h"
#include "BinaryMathOperator.h"
#include "StackManipulator.h"
#include "VariableManipulator.h"
#include "StackOperatorFactory.h"

using namespace Calculator;

#include "Helpers.h"

class ExecutiveTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(ExecutiveTest);

  CPPUNIT_TEST(testAllA);
  CPPUNIT_TEST_SUITE_END();

public:

ExecutiveTest() {
  defaultFactory.addCreator(StackOperatorCreator::Ptr(new NumberCreator()));
  defaultFactory.addCreator(StackOperatorCreator::Ptr(new BinaryMathCreator()));
  defaultFactory.addCreator(StackOperatorCreator::Ptr(new StackManipulatorCreator()));
  defaultFactory.addCreator(StackOperatorCreator::Ptr(new VariableManipulatorCreator()));
  defaultFactory.addCreator(StackOperatorCreator::Ptr(new VariableCreator()));
}

public:

void testAllA() {
Stack stack;
FixedOperatorExecutive f(defaultFactory, stack);

{
const std::string input = "5.0 -10.0 2.5 $foo dup $bar ! ! $bar * / ";
std::istringstream is(input);
std::ostringstream os;
f.process(is, os);

const float expected[] = { -5.0 };
verify(stack, expected);
// TODO: Consider verifying variables
}

{
const std::string input = "-0.1 - .1 + 2 swap ^ $bar @ pop invalid-token $bar @";
std::istringstream is(input);
std::ostringstream os;

f.process(is, os);
const float expected[] = { 25.0, 2.5 };
verify(stack, expected);
// TODO: Consider verifying variables
}
}

private:
StackOperatorFactory defaultFactory;
};

CPPUNIT_TEST_SUITE_REGISTRATION(ExecutiveTest);
