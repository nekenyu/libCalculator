/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef STACK_OPERATOR_H
#define STACK_OPERATOR_H

namespace Calculator {

  class Stack;
  
  /** \brief Base class for all operators.
   *
   * StackOperatorCreators and the StackFactory will return StackOperator::Ptr.
   */
  class StackOperator {
  public:
    typedef std::shared_ptr<StackOperator> Ptr;

    virtual ~StackOperator() { }

  protected:
    StackOperator() = default;
    
    StackOperator(const StackOperator&) = delete;
    StackOperator(StackOperator&&) = delete;
    StackOperator& operator=(const StackOperator&) = delete;
    StackOperator& operator=(StackOperator&&) = delete;
      
  public:
    /** Execute this operator on stack
     *
     * @param stack to operate on
     * @param ofThis is this in a copied StackOperator::Ptr to maintain
     * integrity of the shared_ptrs.
     *
     * @return string result of execution.  Can be any string.  Common strings
     * are listed in Calculator::Errorh
     */
    virtual std::string operator()(Stack& stack, StackOperator::Ptr ofThis) = 0;
  };

  /** \brief Factory creators of StackOperator::Ptrs
   */
  class StackOperatorCreator {
  public:
    typedef std::shared_ptr<StackOperatorCreator> Ptr;
    
    virtual ~StackOperatorCreator() { }

    /** @return Help text for StackOperator::Ptrs this creates */
    virtual std::string getHelp() const = 0;

    /** @return StackOperator::Ptr of the StackOperator created from str, or
     * it will be empty to indicate str cannot be used to create an item of
     * this type.
     */
    virtual StackOperator::Ptr create(const std::string& str) = 0;
  };
  
} // namespace Calculator 

#endif // STACK_OPERATOR_H
