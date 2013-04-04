#ifndef VARIABLE_SET_H
#define VARIABLE_SET_H

#ifndef STACK_ITEM_H
#include "StackItem.h"
#endif // STACK_ITEM_H

namespace Calculator {

/** \class VariableSet
 * \brief All variables belonging to a Stack.
 *
 * A variable without a value is acceptable until its value is requested; such a
 * request is not allowed.
 */
class VariableSet {
private:
typedef std::map<std::string, StackItem::Ptr> MapType;

public:
/** Construct with an empty variable set */
VariableSet() = default;

VariableSet(const VariableSet&) = delete;
VariableSet(VariableSet&&) = delete;
VariableSet& operator=(const VariableSet&) = delete;
VariableSet& operator=(VariableSet&&) = delete;

/** Get the value of name, if any.
 *
 * @param name of the variable go get
 *
 * @return StackItem holding the value of the variable
 */
StackItem::Ptr get(const std::string& name) const;

/** Set the value of name, overriding existing values
 *
 * @param name of the variable go set
 * @param value holding the value of the variable
 */
void set(const std::string& name, StackItem::Ptr value);

private:
/** Map of name to value */
MapType map;
};

} // namespace Calculator

#endif // VARIABLE_SET_H
