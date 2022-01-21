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
#include "Parser/parser.h"
#include "DefintionTree/DefinitionTree.h"
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

    std::string defintion = "fun -> sum(mod(#0, #0), 1)";
    std::string expression = "fun(5)";
    Lexer lex1(defintion);
    Lexer lex2(expression);
    // lex.print();
    std::cout << "smth"; 



    std::vector<std::pair<Token, std::string>> list1 = lex1.exportTokens();
    std::vector<std::pair<Token, std::string>> list2 = lex2.exportTokens();
    //std::vector<std::pair<Token, std::string>>::iterator it = list.begin();
    Parser parse;
    parse.parse(list1);
    std::cout << "strat new" << std::endl;
    parse.parse(list2);

    std::string str = "#0";

    DefinitionNode* smth = new ParamNode(str);
    std::cout << "output: " << (typeid(*smth).hash_code() == typeid(ParamNode).hash_code()) << std::endl;

    return 0;
}