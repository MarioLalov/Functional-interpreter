#pragma once

#include <tuple>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <iostream>

enum class Token
{
    FunName,
    FunDefinition,
    LBracket,
    RBracket,
    LSqBracket,
    RSqBracket,
    Number,
    Comma,
    Argument
};

class Lexer
{
private:
    std::vector<std::pair<Token, std::string>> tokens;

public:
    Lexer(std::string& expression);
    void addSpecial(std::string& symbol);
    std::vector<std::pair<Token, std::string>> exportTokens();
    void print();
};