#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>
#include <string>

#include "../Expression-tree/tree.h"

//interface
class Variable
{
public:
  virtual Variable *execute() = 0;
};

typedef Variable *(*procedure)(std::vector<Variable *>);

#endif