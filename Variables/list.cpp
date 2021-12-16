#include "list.h"

List::List(const std::vector<Number> in_data)
{
    for (std::size_t i = 0; i < in_data.size(); i++)
    {
        data.push_back(data[i]);
    }
}

List::List(const std::string in_list)
{
    std::size_t cnt = 1;

    //loop all chars till the end of the list
    while (in_list[cnt] != ']')
    {
        //skip empty spaces
        if(in_list[cnt] == ' ')
        {
            cnt++;
            continue;
        }

        //get number
        std::string num;
        while (in_list[cnt] != ',' && in_list[cnt] != ' ')
        {
            //end of list
            if(in_list[cnt] == ']')
            {
                data.push_back(std::stof(num));

                return;
            }

            num.push_back(in_list[cnt]);
            cnt++;
        }

        data.push_back(std::stof(num));
        cnt++;
    }
}

Variable *List::execute()
{
    return this;
}

const std::vector<Number> List::getData() const
{
    return data;
}
