#include "lexer.h"

Lexer::Lexer(std::string &expression)
{
    std::stringstream str(expression);

    std::string cur_word;
    char cur;

    while (str.get(cur))
    {
        if (!std::isspace(cur) && cur != ',' && cur != '(' && cur != ')' && cur != '[' && cur != ']')
        {
            cur_word += cur;
        }
        else
        {
            if (!cur_word.empty())
            {
                addSpecial(cur_word);
                cur_word.clear();
            }
        }

        switch (cur)
        {
        case '(':
            tokens.push_back({Token::LBracket, "("});
            addSpecial(cur_word);
            cur_word.clear();
            break;
        case ')':
            tokens.push_back({Token::RBracket, ")"});
            addSpecial(cur_word);
            cur_word.clear();
            break;
        case '[':
            tokens.push_back({Token::LSqBracket, "["});
            addSpecial(cur_word);
            cur_word.clear();
            break;
        case ']':
            tokens.push_back({Token::RSqBracket, "]"});
            addSpecial(cur_word);
            cur_word.clear();
            break;
        case ',':
            tokens.push_back({Token::Comma, ","});
            addSpecial(cur_word);
            cur_word.clear();
            break;
        default:
            break;
        }
    }

    if (!cur_word.empty())
    {
        addSpecial(cur_word);
        cur_word.clear();
    }
}

// add definition to header
bool is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
        
    return !s.empty() && it == s.end();
}

void Lexer::addSpecial(std::string &symbol)
{
    if (symbol.empty())
    {
        return;
    }

    if (symbol == "->")
    {
        tokens.push_back({Token::FunDefinition, symbol});
        return;
    }

    if (symbol[0] == '#' && is_number(symbol.substr(1, symbol.size() - 1)))
    {
        tokens.push_back({Token::Argument, symbol});
        return;
    }

    try
    {
        std::stof(symbol);
        tokens.push_back({Token::Number, symbol});
        return;
    }
    catch (...)
    {
    }

    tokens.push_back({Token::FunName, symbol});
}

std::vector<std::pair<Token, std::string>> Lexer::exportTokens()
{
    return tokens;
}

void Lexer::print()
{
    for (std::size_t i = 0; i < tokens.size(); i++)
    {
        switch (tokens[i].first)
        {
        case Token::LBracket:
            std::cout << "(" << std::endl;
            break;
        case Token::RBracket:
            std::cout << ")" << std::endl;
            break;
        case Token::LSqBracket:
            std::cout << "[" << std::endl;
            break;
        case Token::RSqBracket:
            std::cout << "]" << std::endl;
            break;
        case Token::Comma:
            std::cout << "," << std::endl;
            break;
        case Token::FunDefinition:
            std::cout << "->" << std::endl;
            break;
        case Token::FunName:
            std::cout << "Name: " << tokens[i].second << std::endl;
            break;
        case Token::Argument:
            std::cout << "Arg: " << tokens[i].second << std::endl;
            break;
        case Token::Number:
            std::cout << "Num: " << tokens[i].second << std::endl;
            break;
        default:
            break;
        }
    }
}
