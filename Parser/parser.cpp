#include "parser.h"
/* TOKENS
Name: fun
defition: ->
Name: sum
lbr: (
Name: mod
lbr: (
Arg: #0
com: ,
Arg: #1
rbr: )
com: ,
Num: 1
rbr: )

fun -> sum(mod(#0, #1), 1)
fun(4, 2)
*/

Function::Function(std::string in_name, DefinitionNode *in_node, bool in_default)
{
    name = in_name;
    node = in_node;
    is_default = in_default;
}

void Parser::parseDefinition(std::vector<std::pair<Token, std::string>>::iterator &it,
                             const std::vector<std::pair<Token, std::string>>::iterator &end,
                             DefinitionNode *previous)
{
    while ((*it).first != Token::RBracket)
    {
        switch ((*it).first)
        {
        case Token::FunName:
        {
            DefinitionNode *current = new DefFunctionNode((*it).second);
            previous->addChild(current);
            it += 2;
            parseDefinition(it, end, current);
            ++it;
            if (it == end)
            {
                return;
            }
        }
        break;
        case Token::Argument:
        {
            previous->addChild(new ParamNode((*it).second));
            ++it;
        }
        break;
        case Token::Comma:
            ++it;
            break;
        case Token::Number:
        {
            previous->addChild(new ConstNode(std::stof((*it).second)));
            std::cout << (*it).second;
            ++it;
        }
        break;
        default:
            // throw
            break;
        }
    }
}

void Parser::parse(std::vector<std::pair<Token, std::string>> tokens)
{
    std::vector<std::pair<Token, std::string>>::iterator it = tokens.begin();
    const std::vector<std::pair<Token, std::string>>::iterator &end = tokens.end();

    if ((*it).first == Token::FunName)
    {
        std::string fun_name = (*it).second;

        ++it;
        if ((*it).first == Token::FunDefinition)
        {
            DefinitionNode *head = new DefFunctionNode(fun_name);

            ++it;
            if ((*it).first == Token::FunName)
            {
                parseDefinition(it, end, head);
            }
            else if ((*it).first == Token::Number)
            {
                head->addChild(new ConstNode(std::stof((*it).second)));
            }
            else if ((*it).first == Token::Argument)
            {
                head->addChild(new ParamNode((*it).second));
            }

            definitions.push_back({fun_name, new Tree(head)});
            Tree *tr = new Tree(head);
            tr->print(tr->getRoot());
        }
        else if ((*it).first == Token::LBracket)
        {
            Tree *cur = getDefintion(fun_name);

            parseExpression(++it, end, cur);
            cur->print(cur->getRoot());
        }
    }
}

Tree *Parser::getDefintion(std::string name)
{
    for (std::size_t i = 0; i < definitions.size(); i++)
    {
        if (definitions[i].first == name)
        {
            return definitions[i].second;
        }
    }

    return nullptr;
}

void Parser::parseExpression(std::vector<std::pair<Token, std::string>>::iterator &it,
                             const std::vector<std::pair<Token, std::string>>::iterator &end,
                             Tree *executing_fun)
{
    std::size_t arg_cnt = 0;

    while ((*it).first != Token::RBracket)
    {
        switch ((*it).first)
        {
        case Token::FunName:
        {
            executing_fun->attachArgument(arg_cnt, getDefintion((*it).second)->getRoot());
            ++it;
        }
        break;
        case Token::Comma:
        {
            arg_cnt++;
            ++it;
        }
        break;
        case Token::Number:
        {
            executing_fun->attachArgument(arg_cnt, new ConstNode(std::stof((*it).second)));
            ++it;
        }
        default:
            break;
        }
    }
}

/*
procedure Parser::getDefault(std::string name)
{
    for (std::size_t i = 0; i < defaults.size(); i++)
    {
        if (name == defaults[i].first)
        {
            return defaults[i].second;
        }
    }

    return nullptr;
}*/