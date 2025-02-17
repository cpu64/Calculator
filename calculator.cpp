#include <cctype>
#include <ctime>
#include <string>
#include <unordered_map>
#include "calculator.hpp"
#include "token.hpp"
using std::string;

int verify(const string::iterator it, const string& expr, const string& pre, const string& post){
    if(pre.contains(*(it-1)) && post.contains(*(it+1))){
        return 0;
    }
    return 1;
}

int Calculator::preprocessing(string& expr){
    int parentheses = 0;
    expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());
    expr.push_back('\n');
    expr.insert(0, "\n");
    for(auto it = expr.begin(); it < expr.end(); it++){
                    // std::cout << *it << std::endl;
        if(Calculator::operators.contains(*it)) {

            if(*it == '(') { parentheses++; }
            else if(*it == ')') { parentheses--; }
            if(*it == '-' && (*(it-1) == '\n' || (operators.contains(*(it-1)) && *(it-1) != ')'))) { *it = '\''; }
            if(verify(it, expr, operators[*it].pre, operators[*it].post)) return 1;
        } else if (isdigit(*it)) {
            if(verify(it, expr, (string)"+-'*/(\n"+numbers, (string)"+-'*/)\n"+numbers)) return 1;
        } else if (isalpha(*it)) {
            if(verify(it, expr, (string)"+-'*/(\n"+letters, (string)"+-'*/)\n"+letters)) return 1;
        } else if (isspace(*it)) {
            continue;
        } else { return 1; }
    }
    return parentheses;
}

std::vector<Token> Calculator::build_RPN(const std::vector<Token>& tokeans){
    std::vector<Token> RPN;
    std::vector<Token> buff;
    for(auto it = tokeans.begin(); it < tokeans.end(); it++) {
        if(it->type() == NUMBER) {RPN.push_back(*it);}
        else if (it->type() == OPERATOR) {
            if(buff.size() == 0) {
                buff.push_back(*it);
            } else if (operators[it->value()[0]].precedence > operators[buff.back().value()[0]].precedence) {
                buff.push_back(*it);
            } else if (operators[it->value()[0]].precedence <= operators[buff.back().value()[0]].precedence) {
                while (!buff.empty() && operators[it->value()[0]].precedence <= operators[buff.back().value()[0]].precedence) {
                    RPN.push_back(buff.back());
                    buff.pop_back();
                }
                buff.push_back(*it);
            }
        } else if (it->type() == PARENTHESES) {
            if(it->value() == "(") {
                buff.push_back(*it);
            } else if (it->value() == ")") {
                while (!buff.empty() && buff.back().value() != "(") {
                    RPN.push_back(buff.back());
                    buff.pop_back();
                }
                buff.pop_back();
            }
        } else {
            throw std::invalid_argument((string)"error: while processing tokean: " + it->value());
        }
    }
    for(auto it = buff.rbegin(); it != buff.rend(); ++it) {
        RPN.push_back(*it);
    }
    return std::move(RPN);
}


std::unique_ptr<node> build_ast(const std::vector<Token>& tokeans){
    std::vector<std::unique_ptr<node>> solve;
    for(auto& i : tokeans) {
        if(i.type() == NUMBER) { solve.push_back(std::make_unique<val>(i.value())); }
        else if(i.type() == OPERATOR) {
            if(i.value() == "+"){
                std::unique_ptr<node> op2 = std::move(solve.back());
                solve.pop_back();
                std::unique_ptr<node> op1 = std::move(solve.back());
                solve.pop_back();
                solve.push_back(std::make_unique<add>(std::move(op1), std::move(op2)));
            } else if(i.value() == "-"){
                std::unique_ptr<node> op2 = std::move(solve.back());
                solve.pop_back();
                std::unique_ptr<node> op1 = std::move(solve.back());
                solve.pop_back();
                solve.push_back(std::make_unique<sub>(std::move(op1), std::move(op2)));
            } else if(i.value() == "*"){
                std::unique_ptr<node> op2 = std::move(solve.back());
                solve.pop_back();
                std::unique_ptr<node> op1 = std::move(solve.back());
                solve.pop_back();
                solve.push_back(std::make_unique<mul>(std::move(op1), std::move(op2)));
            } else if(i.value() == "/"){
                std::unique_ptr<node> op2 = std::move(solve.back());
                solve.pop_back();
                std::unique_ptr<node> op1 = std::move(solve.back());
                solve.pop_back();
                solve.push_back(std::make_unique<divv>(std::move(op1), std::move(op2)));
            } else if(i.value() == "'"){
                std::unique_ptr<node> op2 = std::move(solve.back());
                solve.pop_back();
                solve.push_back(std::make_unique<neg>(std::move(op2)));
            }
        }
    }
    return std::move(solve[0]);
}

Calculator::Calculator(string expr){
    root = nullptr;
    if(preprocessing(expr)) throw std::invalid_argument("expression does not follow Calculator's grammar rules.");
    tokeans = Token::tokenize(expr);
    Token::fill_variables(tokeans);
    RPN = build_RPN(tokeans);
    root = build_ast(RPN);
}


double Calculator::solve() {
    return root->evaluate();
}

string Calculator::reverse_polish_notation() {
    string str;
    for(auto& i :RPN)
        str += i.value() + " ";
    str.pop_back();
    return str;
}

string Calculator::print() {
    return root->str();
}
