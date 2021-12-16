#ifndef LIST_H
#define LIST_H

#include "variables.h"
#include "number.h"

class List : public Variable
{
private:
  std::vector<Number> data;

public:
  List(const std::vector<Number> in_data);
  List(const std::string in_list);
  Variable *execute() override;
  const std::vector<Number> getData() const;
};

#endif