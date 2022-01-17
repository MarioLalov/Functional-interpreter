#include <iostream>
#include <vector>
#include <typeinfo>
/*
#include "Variables/variables.h"
#include "Variables/function.h"
#include "Variables/list.h"
#include "Variables/number.h"
#include "Variables/default_function.h"*/

#include "Lexer/lexer.h"
#include <iterator>
#include <string>

void fullPrint(std::vector<std::pair<Token, std::string>>::iterator &it, const std::vector<std::pair<Token, std::string>>::iterator& end);
void print(std::vector<std::pair<Token, std::string>>::iterator &it, const std::vector<std::pair<Token, std::string>>::iterator& end);

int main()
{
    /* Variable *(*add)(std::vector<Variable *>) = substract;
     std::vector<Variable *> args;
     args.push_back(new Number(3.2));
     args.push_back(new Number(3.0));

     std::vector<Variable *> args2;
     args2.push_back(new Number(10.0));
     args2.push_back(new DefaultFunction("add", args, add));

     Variable *test = new DefaultFunction("sub", args2, addition);

     Variable *func = new Function("func", test, args2);

     std::cout << dynamic_cast<Number *>(func->execute())->getData();

     delete test;
 */

    std::string expression = "fun -> sum(mod(#0, #1), 1)";
    Lexer lex(expression);
    // lex.print();

    std::vector<std::pair<Token, std::string>> list = lex.exportTokens();
    std::vector<std::pair<Token, std::string>>::iterator it = list.begin();

    fullPrint(it, list.end());

    return 0;
}

void fullPrint(std::vector<std::pair<Token, std::string>>::iterator &it, const std::vector<std::pair<Token, std::string>>::iterator& end)
{
    if ((*it).first == Token::FunName)
    {
        ++it;
        if ((*it).first == Token::FunDefinition)
        {
            ++it;
            if((*it).first == Token::FunName)
            {
                print(it, end);
            }
            else if((*it).first == Token::Number)
            {
                std::cout << (*it).second << " ";
            }
            else if((*it).first == Token::Argument)
            {
                std::cout << (*it).second << " ";
            }
        }
    }

}

void print(std::vector<std::pair<Token, std::string>>::iterator &it, const std::vector<std::pair<Token, std::string>>::iterator& end)
{
    while ((*it).first != Token::RBracket)
    {
        switch ((*it).first)
        {
        case Token::FunName:
            // atach
            std::cout << (*it).second << "( ";
            it += 2;
            print(it, end);
            ++it;
            if(it == end)
            {
                return;
            }
            break;
        case Token::Argument:
            // atach
            std::cout << (*it).second;
            ++it;
            break;
        case Token::Comma:
            // skip
            std::cout << ", ";
            ++it;
            break;
        case Token::Number:
            // attach const
            std::cout << (*it).second;
            ++it;
            break;
        default:
            std::cout << "Unknown!!!" << (*it).second;
            break;
        }
    }

    std::cout << ")";
}