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

class Function : public Variable
{
protected:
  std::string name;
  Variable *body;

public:
  Function(std::string in_name, Variable *argument);
  Variable *execute() override;
};

class Number : public Variable
{
private:
  float data;

public:
  Number(const float in_data);
  Variable *execute() override;
  const float getData() const;
};

class List : public Variable
{
private:
  std::vector<Number> data;

public:
  List(const std::vector<Number> in_data);
  Variable *execute() override;
  const std::vector<Number> getData() const;
};

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