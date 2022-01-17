#include "syntax-tree.h"

Number::Number(float in_data)
{
    data = in_data;
}

Number Number::operator=(float rhs)
{
    this->data = rhs;
}

Number Number::operator=(Number &rhs)
{
    if (this != &rhs)
    {
        data = rhs.data;
    }
}

List::List(std::vector<Number> in_data)
{
    data = in_data;
}

List::List(float in_first, float in_step)
{
    // first = in_first;
    step = in_step;
}

FunctionNode::FunctionNode(Node *parent)
{
    parent->addChild(this);
}

void FunctionNode::addChild(Node *child)
{
    children.push_back(child);
}

Result *FunctionNode::execute(std::vector<Result *> args)
{
    // set arguments
    for (std::size_t i = 0; i < args.size(); i++)
    {
        aruguments[i]->setData(args[i]);
    }

    // execute functiom
    for (std::size_t i = 0; i < children.size(); i++)
    {
        children[i]->execute();
    }
}

void NumberNode::setData(Result *input)
{
    // validate type

    Number *num_input = dynamic_cast<Number *>(input);

    data = *num_input;
}

Node *createNode(NodeType type, Node *parent)
{
    switch (type)
    {
    case NodeType::Number:
        return new NumberNode(parent);
    case NodeType::List:
        return new ListNode(parent);
    case NodeType::Fucntion:
        return new FunctionNode(parent);
    default:
        break;
    }
}