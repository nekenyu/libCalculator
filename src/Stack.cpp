#include <memory>
#include <vector>
#include <string>
#include <sstream>

#include "Stack.h"

namespace Calculator {

  Stack::Stack()
  {  
  }
  
  Stack::Count Stack::getDepth() const {
    return impl.size();
  }
  
  void Stack::push(StackItem::Ptr item) {
    impl.push_back(item);
  }
  
  bool Stack::pop(const Count items, StackItem::Ptr* to) {
    if(items > impl.size()) {
      return false;
    }
 
    for(int pos = 0; pos < items; ++pos) {
      to[pos] = impl.back();
      impl.pop_back();
    }
    
    return true;
  }

  std::string Stack::toString() const {
    std::ostringstream os;

    os << "[";
    for(SubStackCIter iter = impl.begin(); impl.end() != iter; ++iter) {
      os << " " << (*iter)->getValue();
    }
    os << " ]";

    return os.str();
  }

} // namespace Calculator
