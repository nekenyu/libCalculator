/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include "Stack.h"
#include "Number.h"
#include "Variable.h"
#include "VariableSet.h"
#include "Error.h"

using namespace Calculator;

Result doSomething(Stack& stack) {
  // Create the values we will be reading.  I used item1..item5 for simplicity,
  // but useful names like top, firstNumber, variableToUpdate, maxValue, and
  // actualValue are obviously preferred.
  StackItem::Ptr item1;
  Number::Ptr item2;
  Variable::Ptr item3;
  Number::Ptr item4;
  Variable::Ptr item5;
  
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
    iter.addError(1, Error::NotANumber);
  }

  // Ensure item3 was not dereferenced
  if(!item3) {
    iter.addError(2, Error::NotAVariable);
  }

  // Ensure item4 is a number
  if(!item4) {
    iter.addError(3, Error::NotANumber);
  }

  // Ensure item5 is a Variable
  // Note: For the purpose of example, this will fail as we inserted the number
  if(!item5) {
    iter.addError(4, Error::NotAVariable);
  }

  if(!iter) {
    return iter.getResult();
  }

  // Finally, all is well and we are ready to proceed:
  stack.popAfter(iter);

  // ...
}

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
  stack.push(number);

  // Note that the variable is set after being used
  stack.getVariables().set(variable->getName(), number);

  // Do something with the result
  const Result result = doSomething(stack);
  std::cout << result.toString() << std::endl;

  return 0;
}
