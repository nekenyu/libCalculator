#ifndef STACK_OPERATOR_FACTORY_H
#define STACK_OPERATOR_FACTORY_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {

class StackOperatorFactory {
public:
void addCreator(StackOperatorCreator::Ptr creator);

std::string getHelp() const;
StackOperator::Ptr create(const std::string& str) const;

private:
std::vector<StackOperatorCreator::Ptr> creators;
};

} // namespace Calculator

#endif // STACK_OPERATOR_FACTORY_H
