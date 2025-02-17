#pragma once
#include <string>
#include <vector>

enum Token_type{
    PARENTHESES,
    OPERATOR,
    VARIABLE,
    NUMBER
};

class Token{
    enum Token_type t;
    std::string token;
public:
    Token(const std::string& str, const enum Token_type& type);
    Token(const char& str, const enum Token_type& type);
    enum Token_type type() const;
    std::string value() const;
    static std::vector<Token> tokenize(std::string& expr);
    static void fill_variables(std::vector<Token>& tokeans);
};
