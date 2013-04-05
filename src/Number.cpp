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
#include <string>
#include <sstream>

#include "Stack.h"
#include "Number.h"

namespace {

  std::string format(float f) {
    std::ostringstream os;
    os << f;
    return os.str();
  }

} // anonymous namespace

namespace Calculator {

  Number::Ptr Number::create(float theValue) {
    return Ptr(new Number(theValue));
  }

  Number::~Number() {
  }
  
  Number::Number(float theValue)
    : value(theValue), valueString(format(theValue))
  {
  }
  
  float Number::getValue() const {
    return value;
  }
  
  std::string Number::toString() const {
    return valueString;
  }

  NumberCreator::~NumberCreator() { }

  std::string NumberCreator::getHelp() const {
    return "[number] -- Any of many formats of number to push onto the stack";
  }

  StackOperator::Ptr NumberCreator::create(const std::string& str) {
    std::istringstream is(str);
    float f = 0.0;
    is >> f;

    if(is) {
      char c;
      is >> c;
      if(is.eof()) {
	return Number::create(f);
      }
    }

    return StackOperator::Ptr();
  }

} // namespace Calculator
