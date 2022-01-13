#ifndef DEF_FUN_H
#define DEF_FUN_H

#include <cmath>
#include <typeinfo>
#include "function.h"
#include "number.h"
#include "list.h"

class DefaultFunction : public Function
{
private:
  procedure to_be_executed;

public:
  DefaultFunction(std::string in_name, std::vector<Variable *> in_arguments, procedure in_procedure);
  Variable *execute(std::vector<Variable* > args) override;
};

//default functions
//arithmetics
Variable *addition(std::vector<Variable *> arguments);
Variable *substract(std::vector<Variable *> arguments);
Variable *multiply(std::vector<Variable *> arguments);
Variable *divide(std::vector<Variable *> arguments);
Variable *modulo(std::vector<Variable *> arguments);
Variable *sqareRoot(std::vector<Variable *> arguments);

//helpers
Variable *length(std::vector<Variable *> arguments);





#endif