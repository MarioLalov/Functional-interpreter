#ifndef NUMBER_H
#define NUMBER_H

#include "variables.h"

class Number : public Variable
{
private:
  float data;

public:
  Number(const float in_data);
  Number(const std::string num);
  Variable *execute() override;
  const float getData() const;
};

#endif