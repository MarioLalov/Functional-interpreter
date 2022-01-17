#pragma once

#include <string>
#include <vector>
#include <typeinfo>

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

    virtual ~DefinitionNode();
};

class DefFunctionNode : public DefinitionNode
{
private:
    std::string name;

public:
    DefFunctionNode(std::string &in_name);

    ~DefFunctionNode();
};

class ParamNode : public DefinitionNode
{
private:
    std::string name;

public:
    ParamNode(std::string &in_name);
    std::string getName() const;
    ~ParamNode();
};

class ConstNode : public DefinitionNode
{
private:
    float value;

public:
    ConstNode(float in_value);
};

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
    ~ListNode();
};

class Tree
{
private:
    DefinitionNode *root;

public:
    void attachArgument(std::size_t arg_num, DefinitionNode *arg);
};

DefinitionNode *createDefintion(DefinitionType type, std::string name);
