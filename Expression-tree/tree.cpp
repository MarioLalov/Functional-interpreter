#include "tree.h"

ExpressionNode::ExpressionNode(float in_data)
{
    leaf_data = in_data;
    is_leaf = true;
}

ExpressionNode::ExpressionNode(std::string in_data)
{
    fun_name = in_data;
}

void ExpressionNode::setFunName(std::string in_name)
{
    if(!is_leaf)
    {
        fun_name = in_name;
    }
}

ExpressionTree::ExpressionTree()
{
    root = new ExpressionNode("");
}

ExpressionTree::ExpressionTree(float in_data)
{
    root = new ExpressionNode(in_data);
}