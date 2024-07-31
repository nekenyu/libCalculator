/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef NUMBER_H
#define NUMBER_H

#ifndef STACK_ITEM_H
#include "StackItem.h"
#endif // STACK_ITEM_H

namespace Calculator {
  
  class Stack;
  
  /** StackItem representing a number.
   *
   * These are not re-used and the current value is not modified after creation.
   */
  class Number : public StackItem {
  public:
    typedef std::shared_ptr<Number> Ptr;

    static const std::string indef_type_string()  {
      return "a Number";
    }

    /** Create with theValue to represent.
     *
     * @param theValue to be stored in this
     *
     * @return Number created
     */
    static Number::Ptr create(float theValue);

    virtual ~Number();
    
   protected:
    /** Create with theValue to represent.
     *
     * @param theValue to be stored in this
     */
    Number(float theValue);

    Number() = delete;
    Number(const Number&) = delete;
    Number(Number&&) = delete;
    Number& operator=(const Number&) = delete;
    Number& operator=(Number&&) = delete;
      
  public:
    /** @return the value this represents */
    float getValue() const;

    virtual std::string toString() const;
    
  private:
    /** The value this represents */
    const float value;

    /** The value this represents */
    const std::string valueString;
  };

  /** Creates Numbers from strings that convert to numbers */
  class NumberCreator : public StackOperatorCreator {
  public:
    virtual ~NumberCreator();
 
    virtual std::string getHelp() const;
    virtual StackOperator::Ptr create(const std::string& str);
  };
  
} // namespace Calculator

#endif // NUMBER_H
