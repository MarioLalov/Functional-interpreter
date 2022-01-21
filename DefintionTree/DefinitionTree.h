#pragma once

#include <string>
#include <vector>
#include <typeinfo>
#include <iostream>
#include <queue>

enum class DefinitionType
{
    Function,
    Param,
    Const,
    List
};

class DefinitionNode
{
protected:
    DefinitionType type;
    std::vector<DefinitionNode *> children;

public:
    void addChild(DefinitionNode *node);
    void removeChild(std::size_t child_number);
    bool attachTraverse(DefinitionNode *current, DefinitionNode *parent, std::size_t number, std::string arg_num, DefinitionNode *arg);
    std::vector<DefinitionNode *> getChildren();
    virtual void info() = 0;

 //   virtual ~DefinitionNode();
};

class DefFunctionNode : public DefinitionNode
{
private:
    std::string name;

public:
    DefFunctionNode(std::string &in_name);
    void info() override;

    //~DefFunctionNode();
};

class ParamNode : public DefinitionNode
{
private:
    std::string name;

public:
    ParamNode(std::string &in_name);
    std::string getName() const;
    void info() override;
    //~ParamNode();
};

class ConstNode : public DefinitionNode
{
private:
    float value;

public:
    ConstNode(float in_value);
    void info() override;
};

/*

class ListNode : public DefinitionNode
{
private:
    union
    {
        std::vector<DefinitionNode *> data;
        struct
        {
            float first;
            float step;
            float element_count;
        };
    };

    bool step_list;

public:
void info() override;
    ~ListNode();
};*/

class Tree
{
private:
    DefinitionNode *root;

public:
    Tree(DefinitionNode *in_root);
    void attachArgument(std::size_t arg_num, DefinitionNode *arg);
    DefinitionNode *getRoot();
    void print(DefinitionNode* current);
};

//DefinitionNode *createDefintion(DefinitionType type, std::string name);
