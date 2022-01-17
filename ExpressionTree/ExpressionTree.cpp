#include "ExpressionTree.h"

void ExpressionNode::addChild(ExpressionNode* node)
{
    children.push_back(node);
}

ExpFunctionNode::ExpFunctionNode(std::string in_name, procedure in_procedure)
{
    name = in_name;
    to_be_applied = in_procedure;
}

NumberNode::NumberNode(float in_data)
{
    data = in_data;
}