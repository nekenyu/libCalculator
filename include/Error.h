/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef ERROR_H
#define ERROR_H

namespace Calculator {

  namespace Error {
    /** Operation was successful */
    const std::string Ok = "Ok";

    /** Operation required more items than the Stack had available */
    const std::string StackUnderflow = "Insufficient Stack Arguments";

    /** Qualify an error with a stack position.
     *
     * @param position from the top, with 0 being the top
     * @param error message at position
     *
     * @return error message
     */
    inline std::string atPosition(unsigned int position, const std::string& error) {
      return std::string("At position ") + (0 == position ? std::string("top") : std::to_string(position)) + ": " + error;
    }

    /** Operation required a variable.  Item was not a variable. */
    const std::string NotAVariable = "Value is not a variable";

    /** Operation required a variable.  Variable has not been set. */
    const std::string VariableNotSet = "Variable is not set";

    /** Operation required a Number.  Item was not available. */
    const std::string NotANumber = "Value is not a number";
  };
  
} // namespace Calculator

#endif // ERROR_H
  
