#include "DefinitionTree.h"

DefFunctionNode::DefFunctionNode(std::string &in_name)
{
    name = in_name;
}

void DefFunctionNode::info()
{
    std::cout << "Function: " << this->name << std::endl;
}

void ParamNode::info()
{
    std::cout << "Param: " << this->name << std::endl;
}

ParamNode::ParamNode(std::string &in_name)
{
    name = in_name;
}

void ConstNode::info()
{
    std::cout << "Const: " << this->value << std::endl;
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

bool DefinitionNode::attachTraverse(DefinitionNode *current, DefinitionNode *parent, std::size_t number, std::string arg_num, DefinitionNode *arg)
{
    if (typeid(*current).hash_code() == typeid(ParamNode).hash_code())
    {
        ParamNode *converted = dynamic_cast<ParamNode *>(current);

        if (converted->getName() == arg_num)
        {
            parent->removeChild(number);
            parent->addChild(arg);
            std::cout << "adding" << std::endl;
        }
    }

    for (std::size_t i = 0; i < current->children.size(); i++)
    {
        if (attachTraverse(current->children[i], current, i, arg_num, arg))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

std::vector<DefinitionNode *> DefinitionNode::getChildren()
{
    return children;
}

Tree::Tree(DefinitionNode *in_root)
{
    root = in_root;
}

void Tree::attachArgument(std::size_t arg_num, DefinitionNode *arg)
{
    std::cout << "got: " << arg_num << std::endl;
    std::string arg_str = "#" + std::to_string(arg_num);

    root->attachTraverse(root, nullptr, 0, arg_str, arg);
}

DefinitionNode *Tree::getRoot()
{
    return root;
}

std::string ParamNode::getName() const
{
    return name;
}

void Tree::print(DefinitionNode *root)
{
    // queue to store the elements on the current level
    std::queue<DefinitionNode *> queue;
    queue.push(root);

    while (!queue.empty())
    {
        // get the number of nodes on the current row
        int nodeCount = queue.size();

        while (nodeCount > 0)
        {
            // add to string
            DefinitionNode *current = queue.front();
            if (current)
            {
                current->info();
            }

            queue.pop();

            // add the nodes of the next row
            for (std::size_t i = 0; i < current->getChildren().size(); i++)
            {
                queue.push(current->getChildren()[i]);
            }

            nodeCount--;
        }

        std::cout << "NEW ROW" << std::endl
                  << std::endl;
    }
}