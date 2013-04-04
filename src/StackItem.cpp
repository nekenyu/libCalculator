#include <memory>
#include <vector>
#include <map>
#include <string>

#include "StackItem.h"
#include "Stack.h"
#include "Error.h"

namespace Calculator {
  
  StackItem::~StackItem() {
  }
  
  std::string StackItem::operator()(Stack& stack, StackOperator::Ptr ofThis) {
    stack.push(std::dynamic_pointer_cast<StackItem, StackOperator>(ofThis));
    return Error::Ok;
  }

} // namespace Calculator
