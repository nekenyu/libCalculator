#include <memory>
#include <vector>
#include <map>
#include <string>

#include "VariableSet.h"

namespace Calculator {

StackItem::Ptr VariableSet::get(const std::string& name) const {
MapType::const_iterator found = map.find(name);
if(map.end() == found) {
return StackItem::Ptr();
} else {
return found->second;
}
}

void VariableSet::set(const std::string& name, StackItem::Ptr value) {
map[name] = value;
}

} // namespace Calculator
