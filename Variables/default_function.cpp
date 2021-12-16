#include "default_function.h"

DefaultFunction::DefaultFunction(std::string in_name, std::vector<Variable *> in_arguments, procedure in_procedure)
{
    name = in_name;
    arguments = in_arguments;
    to_be_executed = in_procedure;
}

Variable *DefaultFunction::execute()
{
    std::vector<Variable *> executed;

    for (std::size_t i = 0; i < arguments.size(); i++)
    {
        executed.push_back(arguments[i]->execute());
    }

    return to_be_executed(executed);
}