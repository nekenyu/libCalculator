/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef VARIABLE_SET_H
#define VARIABLE_SET_H

namespace Calculator {

  class StackItem;
  class VariableSetPimpl;
  
  /** \class VariableSet
   * \brief All variables belonging to a Stack.
   *
   * A variable without a value is acceptable until its value is requested; such a
   * request is not allowed.
   */
  class VariableSet {
  public:
    /** Construct with an empty variable set */
    VariableSet();
    
    VariableSet(const VariableSet&) = delete;
    VariableSet(VariableSet&&) = delete;
    VariableSet& operator=(const VariableSet&) = delete;
    VariableSet& operator=(VariableSet&&) = delete;
    
    /** Clear all set variables */
    void clear();

    /** Get the value of name, if any.
     *
     * @param name of the variable go get
     *
     * @return StackItem holding the value of the variable
     */
    std::shared_ptr<StackItem> get(const std::string& name) const;
    
    /** Set the value of name, overriding existing values
     *
     * @param name of the variable go set
     * @param value holding the value of the variable
     */
    void set(const std::string& name, std::shared_ptr<StackItem> value);
    
  private:
    /** Private implementation */
    std::shared_ptr<VariableSetPimpl> pimpl;
  };
  
} // namespace Calculator

#endif // VARIABLE_SET_H
