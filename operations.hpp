#pragma once
#include <string>
#include <sstream>
#include <memory>

static constexpr char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static constexpr char numbers[] = "0123456789";

struct Operator
{
    const char precedence = 0;
    const std::string pre;
    const std::string post;
};

class node{
public:
    virtual double evaluate() = 0;
    virtual std::string str() = 0;
    virtual ~node() = default;
};

class add final : public node{
    std::unique_ptr<node> left = nullptr;
    std::unique_ptr<node> right = nullptr;
public:
    add(std::unique_ptr<node> left, std::unique_ptr<node> right) {
        this->left = std::move(left);
        this->right = std::move(right);
    }
    double evaluate() { return left->evaluate() + right->evaluate(); }
    std::string str() { return "(" + left->str() + "+" + right->str() + ")"; }
};

class sub final : public node{
    std::unique_ptr<node> left = nullptr;
    std::unique_ptr<node> right = nullptr;
public:
    sub(std::unique_ptr<node> left, std::unique_ptr<node> right) {
        this->left = std::move(left);
        this->right = std::move(right);
    }
    double evaluate() { return left->evaluate() - right->evaluate(); }
    std::string str() { return "(" + left->str() + "-" + right->str() + ")"; }
};

class mul final : public node{
    std::unique_ptr<node> left = nullptr;
    std::unique_ptr<node> right = nullptr;
public:
    mul(std::unique_ptr<node> left, std::unique_ptr<node> right) {
        this->left = std::move(left);
        this->right = std::move(right);
    }
    double evaluate() { return left->evaluate() * right->evaluate(); }
    std::string str() { return "(" + left->str() + "*" + right->str() + ")"; }
};

class divv final : public node{
    std::unique_ptr<node> left = nullptr;
    std::unique_ptr<node> right = nullptr;
public:
    divv(std::unique_ptr<node> left, std::unique_ptr<node> right) {
        this->left = std::move(left);
        this->right = std::move(right);
    }
    double evaluate() { return left->evaluate() / right->evaluate(); }
    std::string str() { return "(" + left->str() + "/" + right->str() + ")"; }
};

class neg final : public node{
    std::unique_ptr<node> right = nullptr;
public:
    neg(std::unique_ptr<node> right) {
        this->right = std::move(right);
    }
    double evaluate() { return right->evaluate()*-1; }
    std::string str() { return "(-" + right->str() + ")"; }
};

class val final : public node{
    double value;
public:
    val(const std::string& str) { value = std::stod(str); }
    double evaluate() { return value; }
    std::string str() { return (std::stringstream() << value).str(); }
};
