#ifndef HELPERS_H
#define HELPERS_H

/** Push value as a Number onto stack
 * 
 * @param stack to push onto
 * @param value to push as number
 */
inline void push(Stack& stack, float value) {
  stack.push(Number::create(value));
}

/** Push all of input onto stack
 *
 * @tparam inputLength length of input array to push
 * @param stack to push onto
 * @param input array of values to push
 */
template<unsigned int inputLength>
  void push(Stack& stack, const float (&input)[inputLength]) {
    for(int i = 0; i < inputLength; ++i) {
      push(stack, input[i]);
    }
  }

/** Verify stack is empty, that its depth is zero, that its iterators are equal
 *
 * @param stack to test
 */
inline void verify(Stack& stack) {
  CPPUNIT_ASSERT(0 == stack.getDepth());
  CPPUNIT_ASSERT(stack.end() == stack.begin());
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
void verify(Stack& stack, const float(&expected)[length]) {
  CPPUNIT_ASSERT(length <= stack.getDepth());
  
  StackIterator iter = stack.begin();
  for(unsigned int i = 0; i < length; ++i, ++iter) {
    Number::Ptr value = iter.as<Number>();
    CPPUNIT_ASSERT(value);
    CPPUNIT_ASSERT(abs(expected[length - 1 - i] - value->getValue()) < 2 * std::numeric_limits<float>::epsilon());
  }

  CPPUNIT_ASSERT(stack.end() == iter);
}

#endif // HELPERS_H
