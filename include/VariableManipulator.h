/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef VARIABLE_MANIPULATOR_H
#define VARIABLE_MANIPULATOR_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {

  /** Variable Modifier for Variable Operations
   *
   * Support multiple operations distinguished by the Operation parameter.
   *
   * Operations support separate variable-element manipulations
   */
  class VariableManipulator : public StackOperator {
  public:
    typedef std::shared_ptr<VariableManipulator> Ptr;

    /** \enum Operation Operations supported */
    enum class Operation {
      /** Write the value in next-to-top to variable in top*/
      WRITE,

	/** Replace the top variable with its value */
	READ
      };
    
    /** Create to perform operation.
     *
     * @param op to perform
     *
     * @return VariableManipulator created
     */
    static VariableManipulator::Ptr create(Operation op);

    ~VariableManipulator();

  protected:
    /** Create to perform operation.
     *
     * @param op to perform
     */
    VariableManipulator(Operation op);
    
    VariableManipulator(const VariableManipulator&) = delete;
    VariableManipulator(VariableManipulator&&) = delete;
    VariableManipulator& operator=(const VariableManipulator&) = delete;
    VariableManipulator& operator=(VariableManipulator&&) = delete;

    virtual Result operator()(Stack& stack, StackOperator::Ptr ofThis);
    
  private:
    const Operation op;
  };

  /** Create VariableManipulator from a string */
  class VariableManipulatorCreator : public StackOperatorCreator {
  public:
    virtual ~VariableManipulatorCreator();
 
    virtual std::string getHelp() const;
    virtual StackOperator::Ptr create(const std::string& str);
  };
} // namespace Calculator

#endif // VARIABLE_MANIPULATOR_H
