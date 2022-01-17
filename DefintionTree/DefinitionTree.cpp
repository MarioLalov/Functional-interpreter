#include "DefinitionTree.h"

DefFunctionNode::DefFunctionNode(std::string &in_name)
{
    name = in_name;
}

ParamNode::ParamNode(std::string &in_name)
{
    name = in_name;
}

ConstNode::ConstNode(float in_value)
{
    value = in_value;
}

void DefinitionNode::addChild(DefinitionNode *node)
{
    children.push_back(node);
}

void DefinitionNode::removeChild(std::size_t child_number)
{
    children.erase(children.begin() + child_number);
}

bool DefinitionNode::attachTraverse(DefinitionNode* current, DefinitionNode* parent, std::size_t number, std::string arg_num, DefinitionNode* arg)
{
    if(typeid(current).hash_code() == typeid(ParamNode).hash_code())
    {
        ParamNode* converted = dynamic_cast<ParamNode*>(current);

        if(converted->getName() == arg_num)
        {
            parent->removeChild(number);
            parent->addChild(arg);

            return;
        }
    }

    for(std::size_t i = 0; i < current->children.size(); i++)
    {
        if(attachTraverse(current->children[i], current, i, arg_num, arg))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Tree::attachArgument(std::size_t arg_num, DefinitionNode* arg)
{
    std::string arg_str = "#" + std::to_string(arg_num);

    root->attachTraverse(root, nullptr, 0, arg_str, arg);
}

std::string ParamNode::getName() const
{
    return name;
}