#ifndef STACK_OPERATOR_FACTORY_H
#define STACK_OPERATOR_FACTORY_H

#ifndef STACK_OPERATOR_H
#include "StackOperator.h"
#endif // STACK_OPERATOR_H

namespace Calculator {

/** Factory to create StackOperators and help from StackOperatorCreators.
 *
 * This class is simple for a reason: if you want to change available commands,
 * create a factory for each situation and provide it when relevant.
 *
 * \note When creating StackOperators, the first added creator that can make a
 * StackOperator wins and terminates.  There is no ambiguity or resolution done.
 *
 * \todo Create default factories.
 * To avoid requiring including everything, provide a default numeric factory
 * (no variables or stack ops) and a default full factory.
 */
class StackOperatorFactory {
public:

/** Add creator as available after all previous creators.
 *
 * @param creator to add
 */
void addCreator(StackOperatorCreator::Ptr creator);

/** @return help string for all available creators */
std::string getHelp() const;

/** Try to create a StackOperator for the given str.
 *
 * @param str to use in attempting to create a StackOperator
 *
 * @return StackOperator created, or none if there is no match to str
 */
StackOperator::Ptr create(const std::string& str) const;

private:
/** The creators available in this factory.*/
std::vector<StackOperatorCreator::Ptr> creators;
};

} // namespace Calculator

#endif // STACK_OPERATOR_FACTORY_H
