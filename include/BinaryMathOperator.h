/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef BINARY_MATH_OPERATOR_H
#define BINARY_MATH_OPERATOR_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {

  /** Stack Modifier for Binary Math Operations.
   *
   * Support multiple operations distinguished by the Operation parameter.
   *
   * All Operations pop 2 items, caclulate formerTop (operator) formerSecond
   * and push the result back onto the stack.
   */
  class BinaryMathOperator : public StackOperator {
  public:
    typedef std::shared_ptr<BinaryMathOperator> Ptr;

    /** \enum Operation Operations supported */
    enum class Operation {
      /** Add the two values */
      ADD,

	/** Subtract the two values */
	SUBTRACT,
	
	/** Multiply the two values */
	MULTIPLY,
	
	/** Divide the two values */
	DIVIDE,
	
	/** Raise top to the exponent second */
	EXPONENT
	};

    /** Create to perform operation.
     *
     * @param op to perform
     *
     * @return BinaryMathOperator created
     */
    static BinaryMathOperator::Ptr create(Operation op);

    ~BinaryMathOperator();

  protected:
    /** Create to perform operation.
     *
     * @param op to perform
     */
    BinaryMathOperator(Operation op);
    
    BinaryMathOperator(const BinaryMathOperator&) = delete;
    BinaryMathOperator(BinaryMathOperator&&) = delete;
    BinaryMathOperator& operator=(const BinaryMathOperator&) = delete;
    BinaryMathOperator& operator=(BinaryMathOperator&&) = delete;

  public:
    virtual Result operator()(Stack& stack, StackOperator::Ptr ofThis);
    
  private:
    const Operation op;
  };

  /** Create BinaryMathOperation from a string */
  class BinaryMathCreator : public StackOperatorCreator {
  public:
    virtual ~BinaryMathCreator();
 
    virtual std::string getHelp() const;
    virtual StackOperator::Ptr create(const std::string& str);
  };
} // namespace Calculator

#endif // BINARY_MATH_OPERATOR_H
