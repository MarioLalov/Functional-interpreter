#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>
#include <string>
#include "md5.h"

#include "../Expression-tree/tree.h"
#include "function.h"
#include "list.h"
#include "number.h"

//interface
class Variable
{
protected:
  Variable *body;

public:

  virtual Variable *execute() = 0;
};

typedef Variable *(*procedure)(std::vector<Variable *>);

class InitializationManager
{
  private:
  std::vector<Variable*> variables;
  std::vector<std::string> names;

  public:
  Variable* get(std::string& name) const;
  void push(std::string name, Variable* input);
  Variable* fromStrng(std::string& input);

};



#endif