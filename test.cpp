#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Lexer/lexer.h"

TEST_CASE("Creating tokens with Lexer")
{
    std::string expresion = "fun -> sum(#0,#1)";
    Lexer lex(expresion);

    std::vector<std::pair<Token, std::string>> tokens = lex.exportTokens();
    REQUIRE(tokens[0].first == Token::FunName && tokens[0].second == "fun");
    REQUIRE(tokens[1].first == Token::FunDefinition);
    REQUIRE(tokens[2].first == Token::FunName && tokens[2].second == "sum");
    REQUIRE(tokens[3].first == Token::LBracket);
    REQUIRE(tokens[4].first == Token::Argument && tokens[2].second == "#0");
    REQUIRE(tokens[5].first == Token::Comma);
    REQUIRE(tokens[6].first == Token::Argument && tokens[2].second == "#1");
    REQUIRE(tokens[7].first == Token::RBracket);
}