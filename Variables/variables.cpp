#include "variables.h"

Function::Function(std::string in_name, Variable *argument)
{
    name = in_name;
    body = argument;
}

Variable *Function::execute()
{
    return body->execute();
}

List::List(const std::vector<Number> in_data)
{
    for (std::size_t i = 0; i < in_data.size(); i++)
    {
        data.push_back(data[i]);
    }
}

Variable *List::execute()
{
    return this;
}

const std::vector<Number> List::getData() const
{
    return data;
}

Number::Number(const float in_data)
{
    data = in_data;
}

const float Number::getData() const
{
    return data;
}

Variable *Number::execute()
{
    return this;
}

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