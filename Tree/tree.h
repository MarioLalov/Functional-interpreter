#pragma once

#include <vector>
#include <queue>
#include <string>
#include <typeinfo>
#include <tuple>
//#include "type.h"

class Node
{
public:
    virtual std::vector<Node *> getChildren() = 0;
};

class NumberNode : public Node
{
private:
    float number;

public:
    NumberNode(float data);
    std::vector<Node *> getChildren() override;
    void setValue(float data);
};

class ListNode : public Node
{
private:
    std::vector<Node *> children;

public:
    ListNode(std::vector<Node *> data);
    std::vector<Node *> getChildren() override;
};

class FunctionNode : public Node
{
private:
    std::string name;
    std::vector<Node *> children;

public:
    FunctionNode(std::string in_name, std::vector<Node *> in_children);
    std::vector<Node *> getChildren() override;
};

class SyntaxTree
{
private:
    std::string tree_name;
    Node *root;

public:
    SyntaxTree();
    void insertArgs(Node *current, std::queue<float> &arguments);
};

class DeclarationManager
{
private:
    std::vector<std::pair<std::string, Node *>> declared_functions;

    static DeclarationManager *instance;
    DeclarationManager();

public:
    static DeclarationManager *getInstance();
    Node* search(std::string& name) const;
    void declare(std::string &expression);
};