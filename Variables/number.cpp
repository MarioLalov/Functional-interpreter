#include "number.h"

Number::Number(const float in_data)
{
    body = nullptr;
    data = in_data;
}

Number::Number(const std::string num)
{
    body = nullptr;
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

bool Number::operator==(const Number& other) const
{
    return other.data == data;
}

bool Number::operator!=(const Number& other) const
{
    return !(*this == other);
}