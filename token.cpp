#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "token.hpp"
#include "calculator.hpp"

Token::Token(const std::string& str, const enum Token_type& type) { token = str; t = type; }
Token::Token(const char& str, const enum Token_type& type) { token = str; t = type; }
enum Token_type Token::type() const { return t; }
std::string Token::value() const { return token; }

std::vector<Token> Token::tokenize(std::string& expr) {
    std::vector<Token> tokeans;
    std::string::iterator it = expr.begin();
    while(it < expr.end()) {
        if(isdigit(*it)){
            std::string num;
            while(isdigit(*it)){
                num += *it++;
            }
            tokeans.push_back(Token(num, NUMBER));
        } else if(isalpha(*it)){
            std::string var;
            while(isalpha(*it)){
                var += *it++;
            }
            tokeans.push_back(Token(var, VARIABLE));
        } else if(*it == '(' || *it == ')'){
            tokeans.push_back(Token(*it, PARENTHESES));
            it++;
        } else if(Calculator::operators.contains(*it)){
            tokeans.push_back(Token(*it, OPERATOR));
            it++;
        } else if(isspace(*it)){
            it++;
        } else {
            throw std::invalid_argument((std::string)"error: " + *it + " is unrecognised!");
        }
    }
    return std::move(tokeans);
}

void Token::fill_variables(std::vector<Token>& tokeans){
    std::unordered_map<std::string, std::string> cache;
    for(auto it = tokeans.begin(); it < tokeans.end(); it++) {
        if(it->type() == VARIABLE) {
            if(cache.contains(it->value())){
                *it = Token(cache[it->value()], NUMBER);
            } else {
                ask:
                std::string temp;
                std::cout << std::format("Set value for: {}\n", it->value());
                std::cin >> temp;
                std::cin.ignore();
                try {
                    std::stod(temp);
                    Token tokean = Token(temp, NUMBER);
                    *it = tokean;
                    cache[it->value()] = temp;
                } catch (const std::out_of_range& e) {
                    std::cerr << std::format("Value: {} is too large for a 64 bit float!\n", temp);
                } catch (const std::invalid_argument& e) {
                    std::cerr << std::format("Value: {} could not be converted to a float!\n", temp);
                    goto ask;
                }
            }
        }
    }
}
