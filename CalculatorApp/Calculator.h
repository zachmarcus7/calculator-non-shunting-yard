#include <string>
#include <stack>

#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator
{
    public:
        Calculator();
        std::string evaluate(std::string);
        std::string evaluateExpression(std::string, std::string);
        int applyOperator(int, char, int);
        int toNum(char);
        bool isNum(char);
        bool isOperator(char);
        bool matchingOperator(char, std::string);
};
#endif
