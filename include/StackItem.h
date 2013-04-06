/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef STACK_ITEM_H
#define STACK_ITEM_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {
  
  class Stack;

  /** \class StackItem
   * \brief Base class of all items that can be on the stack.
   */
  class StackItem : public StackOperator {
  public:
    typedef std::shared_ptr<StackItem> Ptr;
    
    virtual ~StackItem();
    
  protected:
    StackItem() = default;
    
    StackItem(const StackItem&) = delete;
    StackItem(StackItem&&) = delete;
    StackItem& operator=(const StackItem&) = delete;
    StackItem& operator=(StackItem&&) = delete;
      
  public:
    /** Execute this item modifying stack.
     *
     * @param stack to process on
     * @param ofThis the StackOperator::Ptr for this object so that its info
     * can be passed around.
     *
     * @return Result from execution
     */
    virtual Result operator()(Stack& stack, StackOperator::Ptr ofThis);

    /** @return string representation of this */
    virtual std::string toString() const = 0;
  };
  
} // namespace Calculator

# endif // STACK_ITEM_H
