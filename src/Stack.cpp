#include <memory>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <set>

#include "Stack.h"
#include "Variable.h"
#include "Error.h"

namespace {
  using namespace Calculator;

  StackItem::Ptr dereferenceVariable(const VariableSet& variables, StackItem::Ptr in) {
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
	return StackItem::Ptr();
      }

      // Dereference curr. An unset reference will be caught by the while loop
      item = variables.get(itemAsVar->getName());
    }
    return StackItem::Ptr();
  }
} // anonymous namespace

namespace Calculator {

  /*
   * StackIterator
   */

  class StackIteratorPimpl {
  public:
    typedef std::vector<StackItem::Ptr>::iterator Iterator;

    StackIterator::Hint hint = StackIterator::Hint::DEREFERENCE_NEXT;
    const VariableSet& variables;
    Iterator iter;

    StackIteratorPimpl(const VariableSet& theVariables, const Iterator& theIter)
    : variables(theVariables), iter(theIter)
    {
    }
  };

  StackIterator::StackIterator(const VariableSet& theVariables, const StackIteratorPimpl::Iterator& theIter)
    : pimpl(PimplPtr(new StackIteratorPimpl(theVariables, theIter)))
  {
  }

  StackIterator::StackIterator(const StackIterator& rhs)
    : pimpl(PimplPtr(new StackIteratorPimpl(rhs.pimpl->variables, rhs.pimpl->iter)))
  {
    pimpl->hint = rhs.pimpl->hint;
  }

  StackIterator& StackIterator::operator=(const StackIterator& rhs) {
    pimpl.reset(new StackIteratorPimpl(rhs.pimpl->variables, rhs.pimpl->iter));
    pimpl->hint = rhs.pimpl->hint;
  }

  StackIterator& StackIterator::operator++() {
    --pimpl->iter;
    return *this;
  }

  StackIterator StackIterator::operator++(int) {
    StackIterator copy = *this;
    --pimpl->iter;
    return copy;
  }

  bool StackIterator::operator==(const StackIterator& rhs) const {
    return rhs.pimpl->iter == pimpl->iter;
  }

  bool StackIterator::operator!=(const StackIterator& rhs) const {
    return rhs.pimpl->iter != pimpl->iter;
  }

  StackItem::Ptr StackIterator::operator*() {
    if(Hint::DEREFERENCE_NEXT == pimpl->hint) {
      return dereferenceVariable(pimpl->variables, *pimpl->iter);
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

  Stack::Stack()
  {  
  }
  
  Stack::Count Stack::getDepth() const {
    return impl.size();
  }

  VariableSet& Stack::getVariables() {
    return variables;
  }

  StackIterator Stack::begin() {
    SubStackIter iter = impl.end();
    --iter;
    return StackIterator(variables, iter);
  }

  StackIterator Stack::end() {
    SubStackIter myRbegin = impl.begin();
    --myRbegin;
    return StackIterator(variables, myRbegin);
  }

  void Stack::popAfter(StackIterator& iter) {
    // Get the iterator and move one step closer to top to erase from it to the
    // end since we are popping after the given
    SubStackIter from = iter.getPimpl()->iter;
    ++from;
    impl.erase(from, impl.end());
  }
  
  StackItem::Ptr Stack::dereference(StackItem::Ptr in) const {
    return dereferenceVariable(variables, in);
  }

  void Stack::push(StackItem::Ptr item) {
    impl.push_back(item);
  }

  std::string Stack::toString() const {
    std::ostringstream os;

    os << "[";
    for(SubStackCIter iter = impl.begin(); impl.end() != iter; ++iter) {
      os << " " << (*iter)->toString();
    }
    os << " ]";

    return os.str();
  }

} // namespace Calculator
