#include "DefinitionTree.h"

DefFunctionNode::DefFunctionNode(std::string &in_name)
{
    name = in_name;
}

DefFunctionNode::DefFunctionNode(const DefFunctionNode &other)
{
    name = other.name;

    for (std::size_t i = 0; i < other.children.size(); i++)
    {
        if (typeid(*other.children[i]).hash_code() == typeid(DefFunctionNode).hash_code())
        {
            this->addChild(new DefFunctionNode(*dynamic_cast<DefFunctionNode *>(other.children[i])));
        }
        else if (typeid(*other.children[i]).hash_code() == typeid(ConstNode).hash_code())
        {
            this->addChild(new ConstNode(*dynamic_cast<ConstNode *>(other.children[i])));
        }
    }
}

std::string DefFunctionNode::getName() const
{
    return name;
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

ParamNode::ParamNode(const ParamNode &other)
{
    name = other.name;
}

void ConstNode::info()
{
    std::cout << "Const: " << this->value << std::endl;
}

ConstNode::ConstNode(float in_value)
{
    value = in_value;
}

ConstNode::ConstNode(const ConstNode &other)
{
    value = other.value;
}

float ConstNode::getValue() const
{
    return value;
}

void DefinitionNode::addChild(DefinitionNode *node)
{
    children.push_back(node);
}

// should remove by id for duplicated argument
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
            if (typeid(*arg).hash_code() == typeid(ConstNode).hash_code())
            {
                // add with copy constructor for multiple params
                parent->removeChild(number);
                parent->addChild(new ConstNode(*dynamic_cast<ConstNode *>(arg)));
                std::cout << "adding" << std::endl;
            }
            else if (typeid(*arg).hash_code() == typeid(DefFunctionNode).hash_code())
            {
                parent->removeChild(number);
                parent->addChild(new DefFunctionNode(*dynamic_cast<DefFunctionNode *>(arg)));
            }
        }
    }

    for (std::size_t i = 0; i < current->children.size(); i++)
    {
        /*if (attachTraverse(current->children[i], current, i, arg_num, arg))
         {
             return true;
         }
         else
         {
             return false;
         }*/
        attachTraverse(current->children[i], current, i, arg_num, arg);
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

DefinitionNode* Tree::_copyHelper(DefinitionNode* other) const
{ 
    if(other == nullptr)
    {
        return nullptr;
    }

    DefinitionNode* newNode = nullptr;

    if(typeid(*other).hash_code() == typeid(ParamNode).hash_code())
    {
        ParamNode* buff = dynamic_cast<ParamNode*>(other);

        newNode = new ParamNode(buff->getName());
    }
    if(typeid(*other).hash_code() == typeid(ConstNode).hash_code())
    {
        ConstNode* buff = dynamic_cast<ConstNode*>(other);

        newNode = new ConstNode(buff->getValue());
    }
    if(typeid(*other).hash_code() == typeid(DefFunctionNode).hash_code())
    {
        DefFunctionNode* buff = dynamic_cast<DefFunctionNode*>(other);

        newNode = new DefFunctionNode(*buff);
    }

    const std::vector<DefinitionNode*> otherChildren = other->getChildren();
    for(std::size_t i = 0; i < otherChildren.size(); i++)
    {
        DefinitionNode* copiedNode = _copyHelper(otherChildren.at(i));

        if(copiedNode)
            newNode->addChild(copiedNode);
    }

    return newNode;
}

Tree* Tree::getCopy() const
{
    Tree* copy = new Tree();
    copy->root = _copyHelper(this->root);
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