#include "function.h"

Function::Function(std::string in_name, Variable *in_body, std::vector<Variable *> in_arguments)
{
    name = in_name;
    arguments = in_arguments;
    body = in_body;
}

Function::Function(std::string in_name, std::string in_body)
{
    name = in_name;

    std::size_t pos = in_body.find("(");

    if (pos == std::string::npos)
    {
        pos = in_body.find("[");

        if (pos == std::string::npos)
        {
            //use list string constructor
            body = new Number(in_body);

            return;
        }
        else
        {
            body = new List(in_body);

            return;
        }
    }
    else
    {
        std::string inner_function = in_body.substr(0, pos);
    }
}

Variable *Function::execute()
{
    return body->execute();
}