/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef STACK_OPERATOR_FACTORY_H
#define STACK_OPERATOR_FACTORY_H

namespace Calculator {
  
  class StackOperator;
  class StackOperatorCreator;
  class StackOperatorFactoryPimpl;
  
  /** Factory to create StackOperators and help from StackOperatorCreators.
   *
   * This class is simple for a reason: if you want to change available commands,
   * create a factory for each situation and provide it when relevant.
   *
   * \note When creating StackOperators, the first added creator that can make a
   * StackOperator wins and terminates.  There is no ambiguity or resolution done.
   */
  class StackOperatorFactory {
  public:

    /** Create */
    StackOperatorFactory();

    StackOperatorFactory(const StackOperatorFactory& rhs);
    StackOperatorFactory(StackOperatorFactory&& rhs);
    StackOperatorFactory& operator=(const StackOperatorFactory& rhs);
    StackOperatorFactory& operator=(StackOperatorFactory&& rhs);

    /** Add creator as available after all previous creators.
     *
     * @param creator to add
     */
    void addCreator(std::shared_ptr<StackOperatorCreator> creator);
    
    /** @return help string for all available creators */
    std::string getHelp() const;
    
    /** Try to create a StackOperator for the given str.
     *
     * @param str to use in attempting to create a StackOperator
     *
     * @return StackOperator created, or none if there is no match to str
     */
    std::shared_ptr<StackOperator> create(const std::string& str) const;
    
  private:
    /** Private implementation */
    std::shared_ptr<StackOperatorFactoryPimpl> pimpl;
  };

} // namespace Calculator

#endif // STACK_OPERATOR_FACTORY_H
