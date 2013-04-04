#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <string>

#include "Stack.h"
#include "StackOperatorFactory.h"
#include "Number.h"
#include "Variable.h"
#include "BinaryMathOperator.h"
#include "StackManipulator.h"
#include "VariableManipulator.h"
#include "Executive.h"

using namespace Calculator;

int main(int argc, char** argv) {
 
  // Create operation factory
  StackOperatorFactory factory;
  factory.addCreator(StackOperatorCreator::Ptr(new NumberCreator()));
  factory.addCreator(StackOperatorCreator::Ptr(new BinaryMathCreator()));
  factory.addCreator(StackOperatorCreator::Ptr(new StackManipulatorCreator()));
  factory.addCreator(StackOperatorCreator::Ptr(new VariableManipulatorCreator()));
  factory.addCreator(StackOperatorCreator::Ptr(new VariableCreator()));

  // Create Stack
  Stack stack;

  // Run from cin/cout
  FixedOperatorExecutive exec(factory, stack);
  exec.doHelp(std::cout);
  exec.process(std::cin, std::cout);

  return 0;
}
