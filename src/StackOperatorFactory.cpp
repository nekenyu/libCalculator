#include <memory>
#include <vector>
#include <sstream>
#include <string>

#include "StackOperatorFactory.h"

namespace Calculator {

  void StackOperatorFactory::addCreator(StackOperatorCreator::Ptr creator) {
    creators.push_back(creator);
  }

  std::string StackOperatorFactory::getHelp() const {
    std::ostringstream os;
    
    for(auto iter = creators.begin(); creators.end() != iter; ++iter) {
      os << (*iter)->getHelp() << std::endl;
    } 

    return os.str();
  }

  StackOperator::Ptr StackOperatorFactory::create(const std::string& str) const {
    for(auto iter = creators.begin(); creators.end() != iter; ++iter) {
      StackOperator::Ptr created = (*iter)->create(str);
      if(created) {
	return created;
      }
    }

    return StackOperator::Ptr();
  }

} // namespace Calculator
