#include <iostream>
#include <vector>
#include <string>

void getList(std::string in_list, std::vector<float>& data)
{
    std::size_t cnt = 1;

    while (in_list[cnt] != ']')
    {
        if(in_list[cnt] == ' ')
        {
            cnt++;
            continue;
        }

        std::string num;
        while (in_list[cnt] != ',' && in_list[cnt] != ' ')
        {
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

int main()
{
    std::string in_list("[1, 2, 3, 4]");
    std::vector<float> data;

    getList(in_list, data);

    for(std::size_t i = 0; i< data.size(); i++)
    {
        std::cout << data[i] << ", ";
    }

    return 0;
}