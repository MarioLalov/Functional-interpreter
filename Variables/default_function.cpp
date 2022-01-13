#include "default_function.h"

DefaultFunction::DefaultFunction(std::string in_name, std::vector<Variable *> in_arguments, procedure in_procedure)
{
    name = in_name;
    arguments = in_arguments;
    to_be_executed = in_procedure;

    body = nullptr;
}

Variable *DefaultFunction::execute(std::vector<Variable* > args)
{
    std::vector<Variable *> executed;

    for (std::size_t i = 0; i < arguments.size(); i++)
    {
        executed.push_back(args[i]->execute());
    }

    return to_be_executed(executed);
}

//default functions
Variable *addition(std::vector<Variable *> arguments)
{
    float total = 0;

    for (std::size_t i = 0; i < arguments.size(); i++)
    {
        total += dynamic_cast<Number *>(arguments[i])->getData();
    }

    return new Number(total);
}

Variable *substract(std::vector<Variable *> arguments)
{
    if (arguments.empty())
    {
        throw std::invalid_argument("Invalid number of arguments in call of function add()\nexpected: at least 1\ngiven: 0");
    }

    float current = dynamic_cast<Number *>(arguments[0])->getData();

    for (std::size_t i = 1; i < arguments.size(); i++)
    {
        current = current - dynamic_cast<Number *>(arguments[i])->getData();
    }

    return new Number(current);
}

Variable *multiply(std::vector<Variable *> arguments)
{
    float total = 1;

    for (std::size_t i = 0; i < arguments.size(); i++)
    {
        total *= dynamic_cast<Number *>(arguments[i])->getData();
    }

    return new Number(total);
}

Variable *divide(std::vector<Variable *> arguments)
{
    if (arguments.empty())
    {
        throw std::invalid_argument("Invalid number of arguments in call of function div()\nexpected: at least 1\ngiven: 0");
    }

    float current = dynamic_cast<Number *>(arguments[0])->getData();

    for (std::size_t i = 1; i < arguments.size(); i++)
    {
        float divisor = dynamic_cast<Number *>(arguments[i])->getData();

        if (divisor == 0)
        {
            throw std::invalid_argument("Division by zero.");
        }

        current = current / divisor;
    }

    return new Number(current);
}

Variable *modulo(std::vector<Variable *> arguments)
{
    if (arguments.size() != 2)
    {
        throw std::invalid_argument("Invalid number of arguments in call of function mod().\nexpected: 2\ngiven: " + arguments.size());
    }

    float first = dynamic_cast<Number *>(arguments[0])->getData();
    float second = dynamic_cast<Number *>(arguments[1])->getData();

    //check if arguments are integers
    if (std::ceil(first) != first || std::ceil(second) != second)
    {
        throw std::invalid_argument("Contract violation.\nexpected: integer\ngiven: double");
    }

    return new Number((int)first % (int)second);
}

Variable *sqareRoot(std::vector<Variable *> arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("Invalid number of arguments in call of function mod().\nexpected: 1\ngiven: " + arguments.size());
    }

    if(arguments[0] < 0)
    {
        throw std::invalid_argument("Contract violation.\nexpected: positive number\ngiven: negative number");
    }

    return new Number(std::sqrt(dynamic_cast<Number *>(arguments[0])->getData()));
}

Variable *length(std::vector<Variable *> arguments)
{
    if (arguments.size() != 1)
    {
        throw std::invalid_argument("Invalid number of arguments in call of function length().\nexpected: 1\ngiven: " + arguments.size());
    }

    if(typeid(arguments[0]).hash_code() == typeid(List*).hash_code())
    {
        return new Number(-1);
    }

    return new Number(dynamic_cast<List *>(arguments[0])->getData().size()); 
}