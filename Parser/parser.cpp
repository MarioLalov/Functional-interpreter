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

void parseDefinition(std::vector<std::pair<Token, std::string>>::iterator &it,
                     const std::vector<std::pair<Token, std::string>>::iterator &end,
                     DefinitionNode *previous)
{
    while ((*it).first != Token::RBracket)
    {
        switch ((*it).first)
        {
        case Token::FunName:
            DefinitionNode *current = new DefFunctionNode((*it).second);
            previous->addChild(current);
            it += 2;
            parseDefinition(it, end, current);
            ++it;
            if (it == end)
            {
                return;
            }
            break;
        case Token::Argument:
            previous->addChild(new ParamNode((*it).second));
            ++it;
            break;
        case Token::Comma:
            ++it;
            break;
        case Token::Number:
            previous->addChild(new ConstNode(std::stof((*it).second)));
            std::cout << (*it).second;
            ++it;
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
        }
        else if ((*it).first == Token::LBracket)
        {
            --it;
        }
    }
}

/*void Parser::parseExpression(std::vector<std::pair<Token, std::string>>::iterator &it,
                             const std::vector<std::pair<Token, std::string>>::iterator &end,
                             ExpressionNode *previous)
{
    while ((*it).first != Token::RBracket)
    {
        switch ((*it).first)
        {
        case Token::FunName:
            procedure current_procedure = getDefault((*it).second);

            if (!current_procedure)
            {
                return;
            }

            // get expression to evaluate
            ExpFunctionNode *current = new ExpFunctionNode((*it).second, current_procedure);
            previous->addChild(current);
            it += 2;
            parseExpression(it, end, current);
            ++it;
            if (it == end)
            {
                return;
            }
            break;
        case Token::Comma:
            ++it;
            break;
        case Token::Number:
            previous->addChild(new NumberNode(std::stof((*it).second)));
            std::cout << (*it).second;
            ++it;
            break;
        default:
            // throw
            break;
        }
    }
}*/

void parseExpression(std::vector<std::pair<Token, std::string>>::iterator &it,
                     const std::vector<std::pair<Token, std::string>>::iterator &end)
{
    while ((*it).first != Token::RBracket)
    {
    }
}

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
}