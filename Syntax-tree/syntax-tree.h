#pragma once
#include <vector>
#include <string>
#include <iostream>

enum class NodeType
{
    Number,
    List,
    Fucntion
};

class Result
{
public:
    virtual std::string output() = 0;
};

class Number : public Result
{
private:
    float data;

public:
    Number(float in_data);
    Number operator=(float rhs);
    Number operator=(Number &rhs);
    std::string output() override;
};

class List : public Result
{
private:
    union
    {
        std::vector<Number> data;

        struct
        {
            Number first;
            float step;
        };
    };

public:
    List(std::vector<Number> in_data);
    List(float in_first, float in_step);
    std::string output() override;
};

class Node
{
public:
    virtual void addChild(Node *child) = 0;
    virtual Result *execute(std::vector<Result *> args) = 0;
    virtual Result *execute() = 0;
    virtual void setData(Result *) = 0;
};

class FunctionNode : public Node
{
private:
    std::vector<Node *> children;
    std::vector<Node *> aruguments;

public:
    FunctionNode(Node *parent);
    void addChild(Node *child) override;
    Result *execute(std::vector<Result *> args) override;
    Result *execute() override;
    void setData(Result *) override;
};

class NumberNode : public Node
{
private:
    Number data;

public:
    NumberNode(Node *parent);
    void addChild(Node *child) override;
    Result *execute(std::vector<Result *> args) override;
    Result *execute() override;
    void setData(Result *) override;
};

class ListNode : public Node
{
private:
    List data;
    std::vector<Node*> children;

public:
    ListNode(Node *parent);
    void addChild(Node *child) override;
    Result *execute(std::vector<Result *> args) override;
    Result *execute() override;
    void setData(Result *) override;
};

Node *createNode(NodeType type, Node *parent);