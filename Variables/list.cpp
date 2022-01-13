#include "list.h"

List::List(const std::vector<Number*> in_data)
{
    for (std::size_t i = 0; i < in_data.size(); i++)
    {
        data.push_back(data[i]);
    }

    body = nullptr;
}

List::List(const std::string in_list)
{
    std::size_t cnt = 1;

    //loop all chars till the end of the list
    while (in_list[cnt] != ']')
    {
        //skip empty spaces
        if (in_list[cnt] == ' ')
        {
            cnt++;
            continue;
        }

        //get 
        std::string num;
        while (in_list[cnt] != ',' && in_list[cnt] != ' ')
        {
            //end of list
            if (in_list[cnt] == ']')
            {
                //data.push_back(std::stof(num));

                return;
            }

            num.push_back(in_list[cnt]);
            cnt++;
        }

        //data.push_back(std::stof(num));
        cnt++;
    }

    body = nullptr;
}

Variable *List::execute(std::vector<Variable* > args)
{
    return this;
}

const std::vector<Number> List::getData() const
{
   // return data;
}

bool List::operator==(const List& other) const
{
    if (data.size() == other.data.size())
    {
        for(std::size_t i = 0; i < data.size(); i++)
        {
            if(data[i] != other.data[i])
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}
