#pragma once

#include "../Lexer/lexer.h"
#include "../DefintionTree/DefinitionTree.h"
#include <iterator>
#include <cmath>

typedef float (*procedure)(std::vector<DefinitionNode *>);

class Function
{
public:
    std::string name;
    DefinitionNode *node;
    bool is_default;

    Function(std::string in_name, DefinitionNode *in_node, bool in_default);
};

class Parser
{
private:
    std::vector<std::pair<std::string, Tree*>> definitions;
    std::vector<std::pair<std::string,procedure>> defaults;

public:
Parser();
    procedure getDefault(std::string name);
    Tree* getDefintion(std::string name);
    void parse(std::vector<std::pair<Token, std::string>> tokens);
    void parseDefinition(std::vector<std::pair<Token, std::string>>::iterator &it,
                         const std::vector<std::pair<Token, std::string>>::iterator &end,
                         DefinitionNode *previous);
    void parseExpression(std::vector<std::pair<Token, std::string>>::iterator &it,
                         const std::vector<std::pair<Token, std::string>>::iterator &end,
                         Tree* executing_fun);
    float executeTree(DefinitionNode* current_node);
};

//defaults
//TODO: add args validation
float addition(std::vector<DefinitionNode *> arguments);
float modulo(std::vector<DefinitionNode *> arguments);