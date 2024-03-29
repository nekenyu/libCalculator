/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef STACK_MANIPULATOR_H
#define STACK_MANIPULATOR_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {

  /** Stack Modifier for Stack Operations
   *
   * Support multiple operations distinguished by the Operation parameter.
   *
   * Operations support separate stack-element manipulations
   */
  class StackManipulator : public StackOperator {
  public:
    /** \enum Operation Operations supported */
    enum class Operation {
      /** Pop the top value off and forget it */
      POP,

	/** Duplicate the top value */
	DUP,
	
	/** Swap the top two elements */
	SWAP,

	/** Clear the entire stack and set of variables */
	RESET,

	/** Clear the entire stack */
	POP_ALL
	};
    
    /** Create to perform operation.
     *
     * @param operation to perform
     *
     * @return StackManipulator created
     */
    static StackManipulator::Ptr create(Operation operation);

    ~StackManipulator();

  private:
    /** Create to perform operation.
     *
     * @param operation to perform
     */
    StackManipulator(Operation operation);
    
    StackManipulator(const StackManipulator&) = delete;
    StackManipulator(StackManipulator&&) = delete;
    StackManipulator& operator=(const StackManipulator&) = delete;
    StackManipulator& operator=(StackManipulator&&) = delete;

  public:
   virtual Result operator()(Stack& stack, StackOperator::Ptr ofThis);
    
  private:
    const Operation op;
  };

  /** Create StackManipulator from a string */
  class StackManipulatorCreator : public StackOperatorCreator {
  public:
    virtual ~StackManipulatorCreator();
 
    virtual std::string getHelp() const;
    virtual StackOperator::Ptr create(const std::string& str);
  };
} // namespace Calculator

#endif // STACK_MANIPULATOR_H
