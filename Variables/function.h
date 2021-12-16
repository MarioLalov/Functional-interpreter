#ifndef FUNCTION_H
#define FUNCTION_H

#include "variables.h"

class Function : public Variable
{
protected:
  std::string name;
  Variable *body;

public:
  Function(std::string in_name, Variable *argument);
  Function(std::string in_name, std::string in_body);
  Variable *execute() override;
};

#endif