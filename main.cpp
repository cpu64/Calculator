#include <iostream>
#include <string>
#include "calculator.hpp"

int main()
{
    std::string expr;
    std::cout << "enter expression:" << std::endl;
    while(getline(std::cin, expr) && !expr.empty()) {
        try {
            Calculator cal(expr);
            std::cout << "Expression in reverse polish notation: " << cal.reverse_polish_notation() << std::endl;
            std::cout << "Expression with parentheses: " << cal.print() << std::endl;
            std::cout << "Solution: " << cal.solve() << std::endl;
            std::cout << "Enter expression again or press Enter to quit." << std::endl;
        } catch (const std::invalid_argument& e){
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}
