#pragma once

#include <vector>
#include <queue>
#include <string>
#include <typeinfo>
//#include "type.h"

enum class NodeType
{
    Number,
    List,
    Function
};

class Node
{
    public:
    virtual std::vector<Node*> getChildren() = 0;
};

class NumberNode : public Node
{
private:
    float number;

public:
    NumberNode(float data);
    std::vector<Node*> getChildren() override;
};

class ListNode : public Node
{
private:
    std::vector<Node *> children;

public:
    ListNode(std::vector<Node *> data);
    std::vector<Node*> getChildren() override;
};

class FunctionNode : public Node
{
private:
    std::string name;
    std::vector<Node *> children;

public:
    FunctionNode(std::string in_name);
    std::vector<Node*> getChildren() override;
};

class SyntaxTree
{
private:
    std::string tree_name;
    Node *root;

public:
    SyntaxTree(std::string &expresion);
    void insertArgs(Node* current, std::queue<float>& arguments);
};