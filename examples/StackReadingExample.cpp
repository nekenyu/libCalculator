#include <vector>
#include <memory>
#include <map>
#include <limits>
#include <string>

#include "Stack.h"
#include "Number.h"
#include "Variable.h"
#include "Error.h"

using namespace Calculator;

int main(int argc, char** argv) {
  // The items we will be using
  Variable::Ptr variable = Variable::create("$test");
  Number::Ptr number = Number::create(1.2345);
  
  // Setup the stack and variables initial values
  Stack stack;
  stack.push(variable);
  stack.push(variable);
  stack.push(variable);
  stack.push(variable);
  stack.push(variable);

  // Note that the variable is set after being used.
  stack.getVariables().set(variable->getName(), number);

  // Create the values we will be reading.  I used item1..item5 for simplicity,
  // but useful names like top, firstNumber, variableToUpdate, maxValue, and
  // actualValue are obviously preferred.
  StackItem::Ptr item1;
  Number::Ptr item2;
  Variable::Ptr item3;
  Number::Ptr item4;
  Number::Ptr item5;
  
  // Get the iterator and >> it to all the values.  Note the NO_DEREFERENCE_NEXT
  // type hints.  DEREFERENCE_NEXT is default and set after each read.
  StackIterator iter = stack.begin();
  iter >> item1
       >> item2
       >> StackIterator::Hint::NO_DEREFERENCE_NEXT >> item3
       >> item4
       >> item5;

  // Ensure item2 is a number
  if(!item2) {
    // TODO: handle error
  }

  // Ensure item3 was not dereferenced
  if(!item3) {
    // TODO: handle error
  }

  // Finally, all is well and we are ready to proceed:
  stack.popAfter(iter);

  return 0;
}
