#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "token.hpp"
#include "operations.hpp"

class Calculator {
    inline static std::unordered_map<char, Operator> operators = {
        {'+', {1, (std::string)")" + letters + numbers              , (std::string)"-'(" + letters + numbers}},
        {'-', {1, (std::string)"+-'*/()" + letters + numbers + "\n" , (std::string)"-'(" + letters + numbers}},
        {'*', {2, (std::string)")" + letters + numbers              , (std::string)"-'(" + letters + numbers}},
        {'/', {2, (std::string)")" + letters + numbers              , (std::string)"-'(" + letters + numbers}},
        {'(', {0, (std::string)"+-'*/(" + "\n"                      , (std::string)"-'(" + letters + numbers}},
        {')', {0, (std::string)")" + letters + numbers              , (std::string)"-*/)" + "\n"}},
        {'\'', {10, (std::string)"+-*/()" + letters + numbers + "\n", (std::string)"-'(" + letters + numbers}}
    };
    std::vector<Token> tokeans;
    std::vector<Token> RPN;
    std::unique_ptr<node> root;
    int preprocessing(std::string& expr);
    std::vector<Token> build_RPN(const std::vector<Token>& tokeans);
public:
    Calculator(std::string);
    double solve();
    std::string reverse_polish_notation();
    std::string print();
friend class Token;
};
