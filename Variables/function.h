#ifndef FUNCTION_H
#define FUNCTION_H

#include "variables.h"
#include "number.h"
#include "list.h"

class Function : public Variable
{
protected:
  std::string name;
  std::vector<Variable *> arguments;

public:
  Function();
  Function(std::string in_name, Variable *in_body, std::vector<Variable *> in_arguments);
  Function(std::string in_name, std::string in_body);
  Variable *execute() override;
};

#endif