/*
Copyright (c) 2013, Komodo Does Inc
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
- Neither the name of the Komodo Does Inc nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <memory>
#include <vector>
#include <sstream>
#include <string>

#include "StackOperatorFactory.h"
#include "StackOperator.h"

namespace Calculator {

  class StackOperatorFactoryPimpl {
  public:
    typedef std::shared_ptr<StackOperatorFactoryPimpl> Ptr;

    /** The creators available in this factory.*/
    std::vector<StackOperatorCreator::Ptr> creators;
  };
  
  StackOperatorFactory::StackOperatorFactory()
    : pimpl(StackOperatorFactoryPimpl::Ptr(new StackOperatorFactoryPimpl()))
  {
  }

  StackOperatorFactory::StackOperatorFactory(const StackOperatorFactory& rhs)
    : pimpl(StackOperatorFactoryPimpl::Ptr(new StackOperatorFactoryPimpl(*(rhs.pimpl))))
  {
  }

  StackOperatorFactory::StackOperatorFactory(StackOperatorFactory&& rhs)
    : pimpl(rhs.pimpl)
  {
    rhs.pimpl.reset();
  }

  StackOperatorFactory& StackOperatorFactory::operator=(const StackOperatorFactory& rhs) {
    pimpl.reset(new StackOperatorFactoryPimpl(*(rhs.pimpl)));
    return *this;
  }

  StackOperatorFactory& StackOperatorFactory::operator=(StackOperatorFactory&& rhs) {
    pimpl = rhs.pimpl;
    rhs.pimpl.reset();
    return *this;
  }

  void StackOperatorFactory::addCreator(std::shared_ptr<StackOperatorCreator> creator) {
    pimpl->creators.push_back(creator);
  }

  std::string StackOperatorFactory::getHelp() const {
    std::ostringstream os;
    
    for(auto iter = pimpl->creators.begin(); pimpl->creators.end() != iter; ++iter) {
      os << (*iter)->getHelp() << std::endl;
    } 

    return os.str();
  }

  StackOperator::Ptr StackOperatorFactory::create(const std::string& str) const {
    for(auto iter = pimpl->creators.begin(); pimpl->creators.end() != iter; ++iter) {
      StackOperator::Ptr created = (*iter)->create(str);
      if(created) {
	return created;
      }
    }

    return StackOperator::Ptr();
  }

} // namespace Calculator
