/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef VARIABLE_H
#define VARIABLE_H

#ifndef STACK_ITEM_H
#include "StackItem.h"
#endif // STACK_ITEM_H

namespace Calculator {
  
  class Stack;
  
  /** StackItem representing a variable.
   *
   * These are not re-used and the current value is not modified after creation.
   */
  class Variable : public StackItem {
  public:
    typedef std::shared_ptr<Variable> Ptr;

    static const std::string indef_type_string() {
      return "a Variable";
    }

    /** Create with theName to represent.
     *
     * @param theName to be stored in this
     *
     * @return the Variable created
     */
    static Variable::Ptr create(const std::string& theName);

    virtual ~Variable();

  protected:
    /** Create with theName to represent.
     *
     * @param theName to be stored in this
     */
    Variable(const std::string& theName);

    Variable() = delete;
    Variable(const Variable&) = delete;
    Variable(Variable&&) = delete;
    Variable& operator=(const Variable&) = delete;
    Variable& operator=(Variable&&) = delete;
      
  public:
    /** @return the name of this Variable */
    const std::string& getName() const;

    virtual std::string toString() const;
    
  private:
    /** The name this represents */
    const std::string name;
  };

  /** Creates Variables from strings that convert to variables */
  class VariableCreator : public StackOperatorCreator {
  public:
    virtual ~VariableCreator();
 
    virtual std::string getHelp() const;
    virtual StackOperator::Ptr create(const std::string& str);
  };
  
} // namespace Calculator

#endif // VARIABLE_H
