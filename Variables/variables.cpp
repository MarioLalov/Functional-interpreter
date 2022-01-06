#include "variables.h"

Variable* InitializationManager::get(std::string& name) const
{
    for(std::size_t i = 0; i < variables.size(); i++)
    {
        if(names[i] == name)
        {
            return variables[i];
        }
    }

    return nullptr;
}

void InitializationManager::push(std::string name, Variable* input)
{
    variables.push_back(input);
    names.push_back(name);
}

Variable* InitializationManager::fromStrng(std::string& input)
{
    

}