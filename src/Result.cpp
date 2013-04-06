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
#include <algorithm>

#include "Result.h"

namespace Calculator {

  Result::Result(std::initializer_list<Message> theMessages) {
    messages.insert(messages.end(), theMessages.begin(), theMessages.end());
  }
  
  Result::Result(std::initializer_list<PositionMessage> thePositionMessages) {
    positionMessages.insert(positionMessages.end(), thePositionMessages.begin(), thePositionMessages.end());
  }
  
  Result::Result(std::initializer_list<Message> theMessages,
		 std::initializer_list<PositionMessage> thePositionMessages
  ) {
    messages.insert(messages.end(), theMessages.begin(), theMessages.end());
    
  }
  
  const Result::Messages& Result::getMessages() const {
    return messages;
  }
  
  bool Result::hasMessage(const std::string& message) const {
    return std::any_of(messages.begin(), messages.end(), 
		       [=](const std::string& str) { return 0 == message.compare(str); });
  }
  
  void Result::addMessage(const std::string& message) {
    messages.push_back(message);
  }
  
  const Result::PositionMessages& Result::getPositionMessages() const {
    return positionMessages;
  }
  
  bool Result::hasPositionMessage(const unsigned int position, const std::string& message) const {
    return std::any_of(positionMessages.begin(), positionMessages.end(), 
		       [=](const PositionMessage& pm) { return position == pm.first && 0 == message.compare(pm.second); });
  }
  
  void Result::addPositionMessage(const unsigned int position, const std::string& message) {
    positionMessages.push_back(PositionMessage(position, message));
    std::sort(positionMessages.begin(), positionMessages.end());
  }
  
  std::string Result::toString() const {
    return toString(">> ");
  }
  
  std::string Result::toString(const std::string& prefix) const {
    std::ostringstream os;
    for(auto message : messages) {
      os << prefix << " " << message << std::endl ;
    }
    for(auto positionMessage : positionMessages) {
      os << prefix << " @" << positionMessage.first << ": " << positionMessage.second << std::endl ;
    }
    return os.str();
  }
  
} // namespace Calculator
