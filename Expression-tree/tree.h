#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <iostream>
#include <vector>

class ExpressionNode
{
  private:
    union {
        std::string fun_name;
        float leaf_data;
    };

    bool is_leaf;

    std::vector<ExpressionNode *> children;

  public:
    ExpressionNode(float in_data);
    ExpressionNode(std::string in_data);
    void setFunName(std::string in_name);
};

class ExpressionTree
{
  private:
    ExpressionNode *root;

  public:
    ExpressionTree();
    ExpressionTree(float in_data);
    ExpressionTree(std::string in_data);
};

#endif