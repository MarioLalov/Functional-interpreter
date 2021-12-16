#include <iostream>
#include <vector>
#include <typeinfo>

#include "Variables/variables.h"
#include "Variables/function.h"
#include "Variables/list.h"
#include "Variables/number.h"
#include "Variables/default_function.h"

Variable *addition(std::vector<Variable *> arguments)
{
    return new Number(dynamic_cast<Number *>(arguments[0])->getData() + dynamic_cast<Number *>(arguments[1])->getData());
}

Variable *substract(std::vector<Variable *> arguments)
{
    return new Number(dynamic_cast<Number *>(arguments[0])->getData() - dynamic_cast<Number *>(arguments[1])->getData());
}

int main()
{
    Variable *(*add)(std::vector<Variable *>) = substract;
    std::vector<Variable *> args;
    args.push_back(new Number(3.2));
    args.push_back(new Number(3.0));

    std::vector<Variable *> args2;
    args2.push_back(new Number(10.0));
    args2.push_back(new DefaultFunction("add", args, add));

    Variable *test = new DefaultFunction("sub", args2, addition);

    Variable *func = new Function("func", test);
    
    std::cout << dynamic_cast<Number *>(func->execute())->getData();

    delete test;

    return 0;
}