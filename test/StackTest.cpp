#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <memory>

#include "Stack.h"
#include "Number.h"

using namespace Calculator;

class StackTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(StackTest);

  CPPUNIT_TEST(testEmpty);
  CPPUNIT_TEST(testPushOne);
  CPPUNIT_TEST(testPushFive);

  CPPUNIT_TEST(testPopOneOfZero);
  CPPUNIT_TEST(testPopOneOfOne);
  CPPUNIT_TEST(testPopTwoOfOne);

  CPPUNIT_TEST_SUITE_END();

public:
  void testEmpty() {
    Stack stack;
    CPPUNIT_ASSERT(0 == stack.getDepth());
  }

  void testPushOne() {
    Stack stack;
    stack.push(StackItem::Ptr(new Number(0.0)));
    CPPUNIT_ASSERT(1 == stack.getDepth());
  }

  void testPushFive() {
    Stack stack;
    stack.push(StackItem::Ptr(new Number(0.0)));
    stack.push(StackItem::Ptr(new Number(2.0)));
    stack.push(StackItem::Ptr(new Number(3.0)));
    stack.push(StackItem::Ptr(new Number(4.0)));
    stack.push(StackItem::Ptr(new Number(5.0)));
    CPPUNIT_ASSERT(5 == stack.getDepth());
  }

  void testPopOneOfZero() {
    Stack stack;

    StackItem::Ptr values[1];
    const bool popped = stack.pop(1, values);
    CPPUNIT_ASSERT(!popped);
    CPPUNIT_ASSERT(0 == stack.getDepth());
    CPPUNIT_ASSERT(!values[0]);
  }

  void testPopOneOfOne() {
    Stack stack;
    stack.push(StackItem::Ptr(new Number(0.0)));

    StackItem::Ptr values[1];
    const bool popped = stack.pop(1, values);

    CPPUNIT_ASSERT(popped);
    CPPUNIT_ASSERT(0 == stack.getDepth());
    CPPUNIT_ASSERT(values[0]);
    CPPUNIT_ASSERT(0.0 == values[0]->getValue());
  }

  void testPopTwoOfOne() {
    Stack stack;
    stack.push(StackItem::Ptr(new Number(0.0)));

    StackItem::Ptr values[2];
    const bool popped = stack.pop(2, values);
    CPPUNIT_ASSERT(!popped);
    CPPUNIT_ASSERT(1 == stack.getDepth());
    CPPUNIT_ASSERT(!values[0]);
    CPPUNIT_ASSERT(!values[1]);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(StackTest);
