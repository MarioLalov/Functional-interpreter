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

float addition(std::vector<DefinitionNode *> arguments)
{
    float total = 0;

    for (std::size_t i = 0; i < arguments.size(); i++)
    {
        total += dynamic_cast<ConstNode *>(arguments[i])->getValue();
    }

    return total;
}

float modulo(std::vector<DefinitionNode *> arguments)
{
    if (arguments.size() != 2)
    {
        throw std::invalid_argument("Invalid number of arguments in call of function mod().\nexpected: 2\ngiven: " + arguments.size());
    }

    float first = dynamic_cast<ConstNode *>(arguments[0])->getValue();
    float second = dynamic_cast<ConstNode *>(arguments[1])->getValue();

    //check if arguments are integers
    if (std::ceil(first) != first || std::ceil(second) != second)
    {
        throw std::invalid_argument("Contract violation.\nexpected: integer\ngiven: double");
    }

    return ((int)first % (int)second);
}

Parser::Parser()
{
    defaults.push_back({"add", addition});
    defaults.push_back({"mod", modulo});
}

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
            Tree *treeCopy = cur->getCopy();

            parseExpression(++it, end, cur);
            cur->print(cur->getRoot());
            std::cout << "result: " << executeTree(cur->getRoot()) << std::endl;
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
    //must use tree copy 
    std::size_t arg_cnt = 0;

    while ((*it).first != Token::RBracket)
    {
        switch ((*it).first)
        {
        case Token::FunName:
        {
            //do some checks here
            Tree* fun = getDefintion((*it).second);
            executing_fun->attachArgument(arg_cnt, new DefFunctionNode(*dynamic_cast<DefFunctionNode *>(fun->getRoot())));
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

//add errors for incorrectly defined fucntions
float Parser::executeTree(DefinitionNode* current_node)
{
    if(typeid(*current_node).hash_code() == typeid(DefFunctionNode).hash_code())
    {
        std::string fun_name = dynamic_cast<DefFunctionNode*>(current_node)->getName();
        procedure current_procedure = getDefault(fun_name);

        if(current_procedure)
        {
            std::vector<DefinitionNode*> args;
            for(std::size_t i = 0; i < current_node->getChildren().size(); i++)
            {
                args.push_back(new ConstNode(executeTree(current_node->getChildren()[i])));
            }

            return current_procedure(args);
        }
        else
        {
            //only one argument which is a default or other function
            return executeTree(current_node->getChildren()[0]);
        }
    }
    else
    {
        return dynamic_cast<ConstNode*>(current_node)->getValue();
    }
}