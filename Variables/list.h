#ifndef LIST_H
#define LIST_H

#include "variables.h"
#include "number.h"

class List : public Variable
{
private:
  std::vector<Variable*> data;

public:
  List(const std::vector<Number*> in_data);
  List(const std::string in_list);
  Variable *execute(std::vector<Variable* > args) override;
  const std::vector<Number> getData() const;
  bool operator==(const List& other) const;
};

#endif