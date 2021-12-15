#include <iostream>
#include <vector>
#include <typeinfo>

#include "Variables/variables.h"

Variable *addition(std::vector<Variable *> arguments)
{
    return new Number(dynamic_cast<Number *>(arguments[0])->getData() + dynamic_cast<Number *>(arguments[1])->getData());
}

int main()
{
    Variable *(*add)(std::vector<Variable *>) = addition;
    std::vector<Variable *> args;
    args.push_back(new Number(3.2));
    args.push_back(new Number(3.0));

    std::vector<Variable *> args2;
    args2.push_back(new Number(1.0));
    args2.push_back(new DefaultFunction("add", args, add));

    Variable *test = new DefaultFunction("add", args2, add);

    Variable *func = new Function("func", test);
    
    std::cout << dynamic_cast<Number *>(func->execute())->getData();

    delete test;

    return 0;
}