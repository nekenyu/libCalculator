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
#include <set>
#include <string>
#include <sstream>

#include "Stack.h"
#include "Variable.h"
#include "VariableSet.h"
#include "Error.h"

namespace Calculator {

  /*
   * StackIterator
   */
  
  class StackIteratorPimpl {
  public:
    typedef std::shared_ptr<StackIteratorPimpl> Ptr;
    typedef std::vector<StackItem::Ptr>::iterator Iterator;
    
    StackIterator::Hint hint = StackIterator::Hint::DEREFERENCE_NEXT;
    Stack& stack;
    Iterator iter;
    unsigned int position = 0;
    Result result;
    
    StackIteratorPimpl(Stack& theStack, const Iterator& theIter)
      : stack(theStack), iter(theIter)
    {
    }
    
    void addError(unsigned int position, const std::string& error);
    StackItem::Ptr dereference(StackItem::Ptr in);
  };
  
  void StackIteratorPimpl::addError(unsigned int position, const std::string& error) {
    result.addPositionMessage(position, error);
  }

  StackItem::Ptr StackIteratorPimpl::dereference(StackItem::Ptr in) {
    Variable::Ptr asVariable = std::dynamic_pointer_cast<Variable, StackItem>(in);
    if(!asVariable) {
      return in;
    }

    std::set<std::string> varNames;

    StackItem::Ptr item = in;
    while(item) {
      Variable::Ptr itemAsVar = std::dynamic_pointer_cast<Variable, StackItem>(item);
      if(!itemAsVar) {
	return item;
      }

      // Add the current name to the list we've been through, unless already
      // present.  If already present, we have a circle and cannot dereference
      auto result = varNames.insert(itemAsVar->getName());
      if(!result.second) {
	addError(position, Error::VariableReferencesSelf);
	return StackItem::Ptr();
      }

      // Dereference curr. An unset reference will be caught by the while loop
      item = stack.getVariables().get(itemAsVar->getName());
    }

    addError(position, Error::VariableNotSet);
    return StackItem::Ptr();
  }

  StackIterator::StackIterator(std::shared_ptr<StackIteratorPimpl> thePimpl)
    : pimpl(thePimpl)
  {
  }

  StackIterator::StackIterator(const StackIterator& rhs)
    : pimpl(PimplPtr(new StackIteratorPimpl(rhs.pimpl->stack, rhs.pimpl->iter)))
  {
    pimpl->hint = rhs.pimpl->hint;
  }

  StackIterator& StackIterator::operator=(const StackIterator& rhs) {
    pimpl.reset(new StackIteratorPimpl(rhs.pimpl->stack, rhs.pimpl->iter));
    pimpl->hint = rhs.pimpl->hint;
	return *this;
  }

  StackIterator& StackIterator::operator++() {
    if(pimpl->stack.end() != *this) {
      --pimpl->iter;
    }
    ++pimpl->position;
    return *this;
  }

  StackIterator StackIterator::operator++(int) {
    StackIterator copy = *this;
    ++*this;
    return copy;
  }

  bool StackIterator::operator==(const StackIterator& rhs) const {
    return rhs.pimpl->iter == pimpl->iter;
  }

  bool StackIterator::operator!=(const StackIterator& rhs) const {
    return rhs.pimpl->iter != pimpl->iter;
  }

  StackIterator::operator bool() const {
    return 0 == pimpl->result.getPositionMessages().size();
  }

  StackItem::Ptr StackIterator::operator*() {
    if(pimpl->stack.end() == *this) {
      addError(Calculator::Error::StackUnderflow);
      return StackItem::Ptr();
    } else if(Hint::DEREFERENCE_NEXT == pimpl->hint) {
      return pimpl->dereference(*pimpl->iter);
    } else {
      pimpl->hint = Hint::DEREFERENCE_NEXT;
      return *pimpl->iter;
    }
  }

  StackItem::Ptr StackIterator::noDereference() {
    return *pimpl->iter;
  }

  StackIterator& StackIterator::setHint(Hint theHint) {
    pimpl->hint = theHint;
    return *this;
  }

  const Result& StackIterator::getResult() const {
    return pimpl->result;
  }

  void StackIterator::addError(unsigned int position, const std::string& message) {
    pimpl->addError(position, message);
  }

  void StackIterator::addError(const std::string& message) {
    addError(pimpl->position, message);
  }

  StackIterator::PimplPtr StackIterator::getPimpl() {
    return pimpl;
  }

  StackIterator& operator>>(StackIterator& iter, StackIterator::Hint hint) {
    iter.setHint(hint);
    return iter;
  }
  
  StackIterator& operator>>(StackIterator& iter, StackItem::Ptr& t) {
    t = *iter;
    ++iter;
    return iter;
  }

  /*
   * Stack
   */

  class StackPimpl {
  public:
    typedef std::vector<StackItem::Ptr> StackType;
    typedef StackType::iterator Iter;
    typedef StackType::const_iterator CIter;

    /** Implementation of the Stack */
    StackType stack;

    /** Variables used in the Stack
     *
     * This could be isolated into a derived class to provide both types; however,
     * this would require a cast for the Variable suppor classes to get/set the
     * variables...  We will just add it to the only Stack class for now.
     */
    VariableSet variables;
  };

  Stack::Stack()
    : pimpl(PimplPtr(new StackPimpl()))
  {  
  }
  
  Stack::Count Stack::getDepth() const {
    return pimpl->stack.size();
  }

  VariableSet& Stack::getVariables() {
    return pimpl->variables;
  }

  void Stack::reset() {
    popAll();
    pimpl->variables.clear();
  }

  void Stack::popAll() {
    pimpl->stack.clear();
  }

  StackIterator Stack::begin() {
    StackPimpl::Iter iter = pimpl->stack.end();
    --iter;
    return StackIterator(StackIteratorPimpl::Ptr(new StackIteratorPimpl(*this, iter)));
  }

  StackIterator Stack::end() {
    StackPimpl::Iter myRbegin = pimpl->stack.begin();
    --myRbegin;
    return StackIterator(StackIteratorPimpl::Ptr(new StackIteratorPimpl(*this, myRbegin)));
  }

  void Stack::popAfter(StackIterator& iter) {
    // Get the iterator and move one step closer to top to erase from it to the
    // end since we are popping after the given
    StackPimpl::Iter from = iter.getPimpl()->iter;
    ++from;
    pimpl->stack.erase(from, pimpl->stack.end());
  }
  
  void Stack::push(StackItem::Ptr item) {
    pimpl->stack.push_back(item);
  }

  std::string Stack::toString() const {
    std::ostringstream os;

    os << "[";
    for(StackPimpl::CIter iter = pimpl->stack.begin(); pimpl->stack.end() != iter; ++iter) {
      os << " " << (*iter)->toString();
    }
    os << " ]";

    return os.str();
  }

} // namespace Calculator
