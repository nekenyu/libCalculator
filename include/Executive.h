/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CALCULATOR_H
#define CALCULATOR_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {
  
  class Stack;
  class StackOperatorFactory;
  
  /** \class Executive
   * \brief Drivable class to run the calculator with a variable factory per
   * process call to support changing command sets.
   */
  class Executive {
  public:
    /** Create with the stack to process
     *
     * @param stack to process
     */
    Executive(Stack& stack);
    
    Executive(const Executive&) = delete;
    Executive(Executive&&) = delete;
    Executive& operator=(const Executive&) = delete;
    Executive& operator=(Executive&&) = delete;
    
    /** @return string representation of the current state */
    std::string toString() const;

    /** Process commands from input and pushing generated info to output
     *
     * @param factory to parse input and generate Operators from
     * @param input to read commands from
     * @param output to write status to
     */
    void process(StackOperatorFactory& factory, std::istream& input, std::ostream& output);

    /** Process commands from input and pushing generated info to output
     *
     * @param factory to parse input and generate Operators from
     * @param input to create one operator and execute from
     *
     * @return Result of processing
     */
    Result process(StackOperatorFactory& factory, const std::string& input);

    /** Process oper upon the Stack.
     *
     * @param oper to process on the Stack
     *
     * @return Result of processing
     */
    Result process(StackOperator::Ptr oper);
    
    /** @return the count of processed operations */
    unsigned int getOperationCount() const;

    /** Generate help info for this executive to output.
     *
     * @param factory providing commands to get help from
     * @param output to write help info to
     */
    void doHelp(const StackOperatorFactory& factory, std::ostream& output) const;

  private:
    Stack& stack;
    unsigned int operationCount;
  };

  /** \class FixedOperatorExecutive
   * \brief Drivable class to run the calculator with a single set of commands.
   */
  class FixedOperatorExecutive {
  public:
    FixedOperatorExecutive(StackOperatorFactory& theFactory, Stack& theStack);

    FixedOperatorExecutive(const Executive&) = delete;
    FixedOperatorExecutive(Executive&&) = delete;
    FixedOperatorExecutive& operator=(const Executive&) = delete;
    FixedOperatorExecutive& operator=(Executive&&) = delete;
    
    void doHelp(std::ostream& output) const;

    /** Process commands from input and pushing generated info to output
     *
     * @param input to read commands from
     * @param output to write status to
     */
    void process(std::istream& input, std::ostream& output);

    /** Process commands from input and pushing generated info to output
     *
     * @param input to create one operator and execute from
     *
     * @return Result of Processing
     */
    Result process(const std::string& input);

  private:
    Executive executive;
    StackOperatorFactory& factory;
  };
  
} // namespace Calculator

#endif // CALCULATOR_H
