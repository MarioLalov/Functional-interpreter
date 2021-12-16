#include "function.h"

Function::Function(std::string in_name, Variable *argument)
{
    name = in_name;
    body = argument;
}

Function::Function(std::string in_name, std::string in_body)
{
    

}

Variable *Function::execute()
{
    return body->execute();
}