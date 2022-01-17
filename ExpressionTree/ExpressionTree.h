#pragma once

#include <iostream>
#include <vector>

typedef float (*procedure)(std::vector<ExpressionNode *>);

class ExpressionNode
{
protected:
    std::vector<ExpressionNode *> children;

public:
    void addChild(ExpressionNode *node);
    virtual ~ExpressionNode();
};

class ExpFunctionNode : public ExpressionNode
{
private:
    std::string name;
    procedure to_be_applied;

public:
ExpFunctionNode(std::string in_name, procedure in_procedure);
    ~ExpFunctionNode();
};

class NumberNode : public ExpressionNode
{
private:
    float data;

public:
    NumberNode(float in_data);
    ~NumberNode();
};
