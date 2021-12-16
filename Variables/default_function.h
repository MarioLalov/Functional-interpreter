#ifndef DEF_FUN_H
#define DEF_FUN_H

#include "variables.h"

class DefaultFunction : public Variable
{
private:
  std::string name;
  std::vector<Variable *> arguments;
  procedure to_be_executed;

public:
  DefaultFunction(std::string in_name, std::vector<Variable *> in_arguments, procedure in_procedure);
  Variable *execute() override;
};

#endif