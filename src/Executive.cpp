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
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#include "Executive.h"
#include "Stack.h"
#include "StackOperatorFactory.h"
#include "Error.h"

namespace Calculator {

Executive::Executive(Stack& theStack)
  : stack(theStack), operationCount(0)
{
}

void Executive::process(StackOperatorFactory& factory, std::istream& input, std::ostream& output) {
  output << toString() << endl;
  while(true) {
    std::string command;
    input >> command;
    if(!input) {
      break;
    }

    Result result = process(factory, command);
    if(result.hasMessage("quit")) {
      output << "User requested quit..." << endl;
      return;
    }
    
    output << result.toString(std::string(">> ") + std::to_string(operationCount));
    output << toString() << endl;
  }
}

std::string Executive::toString() const {
  return std::string("Stack: ") + stack.toString();
}

Result Executive::process(StackOperatorFactory& factory, const std::string& input) {
  if(0 == input.compare("quit")) {
    return Result({Error::Ok, "quit"});
  }

 if(0 == input.compare("help")) {
    std::ostringstream os;
    doHelp(factory, os);

    return Result({Error::Ok, os.str()});
  }
  
  StackOperator::Ptr op = factory.create(input);
  if(!op) {
    return Result({std::string("Ignoring invalid input: \"") + input + "\""});
  }
  
  return process(op);
}

Result Executive::process(StackOperator::Ptr oper) {
  if(!oper) {
    return Result({"Internal Error: Invalid Operator"});
  }

  Result results = (*oper)(stack, oper);

  ++operationCount;

  return results;
}

unsigned int Executive::getOperationCount() const {
  return operationCount;
}

  void Executive::doHelp(const StackOperatorFactory& factory, ostream& output) const {
  output << "Stack-based calculator." << endl;
  output << "Commands:" << endl;
  output << "\tquit -- exit the program" << endl;
  output << "\thelp -- help for the program" << endl;

  output << endl;
  output << factory.getHelp();
}

FixedOperatorExecutive::FixedOperatorExecutive(StackOperatorFactory& theFactory, Stack& theStack)
  : executive(theStack), factory(theFactory)
{
}
  
void FixedOperatorExecutive::doHelp(std::ostream& output) const {
  executive.doHelp(factory, output);
}

void FixedOperatorExecutive::process(std::istream& input, std::ostream& output) {
  executive.process(factory, input, output);
}

Result FixedOperatorExecutive::process(const std::string& input) {
  return executive.process(factory, input);
}

} // namespace Caclulator
