#include "number.h"

Number::Number(const float in_data)
{
    data = in_data;
}

Number::Number(const std::string num)
{
    data = std::stof(num);
}

const float Number::getData() const
{
    return data;
}

Variable *Number::execute()
{
    return this;
}