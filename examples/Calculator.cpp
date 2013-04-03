#include <memory>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

#include "Stack.h"
#include "StackOperatorFactory.h"
#include "Number.h"
#include "BinaryMathOperator.h"
#include "StackManipulator.h"
#include "Executive.h"

using namespace Calculator;

int main(int argc, char** argv) {
 
  // Create operation factory
  StackOperatorFactory factory;
  factory.addCreator(StackOperatorCreator::Ptr(new NumberCreator()));
  factory.addCreator(StackOperatorCreator::Ptr(new BinaryMathCreator()));
  factory.addCreator(StackOperatorCreator::Ptr(new StackManipulatorCreator()));

  // Create Stack
  Stack stack;

  // Run from cin/cout
  FixedOperatorExecutive exec(factory, stack);
  exec.doHelp(cout);
  exec.process(cin, cout);

  return 0;
}
