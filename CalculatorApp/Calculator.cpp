#include "Calculator.h"


/****************************************************************
* Default Constructor.
*****************************************************************/
Calculator::Calculator()
{
}

/****************************************************************
* This is the main method for evaluating an expression.
*****************************************************************/
std::string Calculator::evaluate(std::string expression)
{
    // create variables for keeping track of values
    std::string simplified = "";
    std::string current = "";
    int curNum = 0;
    int prevNum = 0;
    int start = 0;

    // need to check if expression contains parentheses
    if ((expression.find("(") != std::string::npos) || (expression.find(")") != std::string::npos))
    {
        // create a stack of ints for storing opening parentheses locations
        std::stack<int> openings;

        // first, need to simplify the expressions inside parentheses
        for (int i = 0; i < expression.size(); i++)
        {
            if (expression[i] == '(')
            {
                openings.push(i);
            }
            // check if we're at a number or operator outside of parentheses
            else if (openings.empty())
            {
                // check if there's anything in the current variable
                if (!current.empty())
                {
                    simplified += current;
                    current = "";
                }

                // add on the value outside of the parentheses
                simplified += expression[i];
            }
            else if (expression[i] == ')')
            {
                // create and simplify substring within the parentheses
                openings.pop();
                current = evaluateExpression(current, "*/");
                current = evaluateExpression(current, "+-");
            }
            // this is for when there's an open parenthesis on the stack, but we haven't found the closing yet
            else
            {
                current += expression[i];
            }
        }

        // check if there's anything left over in the current variable
        if (!current.empty())
        {
            simplified += current;
            current = "";
        }

        // once we've simplified expressions inside of parentheses
        // now we need to apply the operators in order
        simplified = evaluateExpression(simplified, "*/");
        simplified = evaluateExpression(simplified, "+-");
        return simplified;
    }
    // otherwise, if the expression doesn't contain any parentheses, can jump straight
    // to applying the operators in order
    else
    {
        simplified = evaluateExpression(expression, "*/");
        simplified = evaluateExpression(simplified, "+-");
        return simplified;
    }
}

/****************************************************************
* This is the actual method for evaluating an expression with no parentheses.
* The operators param is used to evaluate for only the passed operators
*****************************************************************/
std::string Calculator::evaluateExpression(std::string expression, std::string operators) {

    std::string simplified;
    std::string curExpr;
    int curNum = 0;
    int prevNum = 0;
    int prevNumLength = 0;
    bool foundOperator = false;
    char foundOperatorType;

    for (int i = 0; i < expression.size(); i++)
    {
        // check if we're at a number
        if (isNum(expression[i]))
        {
            // get the whole value of the current number
            curNum = toNum(expression[i]);

            // check if there are numbers after this
            while (i < expression.size() && isNum(expression[i + 1]))
            {
                // combine the next number with the current one
                i++;
                curNum = (curNum * 10) + toNum(expression[i]);
            }

            // otherwise, if we have found the operator, get the result of applying it
            if (foundOperator)
            {
                int res = applyOperator(prevNum, foundOperatorType, curNum);
                prevNum = res;
            }
            else
                prevNum = curNum;
        }
        // check if we're at the passed operator
        else if (matchingOperator(expression[i], operators))
        {
            foundOperator = true;
            foundOperatorType = expression[i];
        }
        // check if we're at a space
        else if (expression[i] == 32)
        {
            continue;
        }
        else
        {
            // here, we're adding on any unmatching operators
            simplified += std::to_string(prevNum);
            simplified += expression[i];
            foundOperator = false;
        }
    }

    // still need to add on the previous number at the very of the loop
    simplified += std::to_string(prevNum);

    return simplified;
}

/****************************************************************
* This method just applies the operator between the two passed numbers.
*****************************************************************/
int Calculator::applyOperator(int firstNum, char sign, int secondNum)
{
    if (sign == '*')
    {
        return firstNum * secondNum;
    }
    else if (sign == '/')
    {
        return firstNum / secondNum;
    }
    else if (sign == '+')
    {
        return firstNum + secondNum;
    }
    else if (sign == '-')
    {
        return firstNum - secondNum;
    }
}

/****************************************************************
* This is for getting the numeric value of a char.
*****************************************************************/
int Calculator::toNum(char letter)
{
    // get the ASCII value of the character and convert it
    return (int)letter - 48;
}

/****************************************************************
* This is for checking if a letter is a number (using ASCII).
*****************************************************************/
bool Calculator::isNum(char letter)
{
    return (letter >= 48 && letter <= 57) ? true : false;
}

/****************************************************************
* This is for checking if a letter is an operator.
*****************************************************************/
bool Calculator::isOperator(char letter)
{
    if (letter == '+' || letter == '-' || letter == '*' || letter == '/')
    {
        return true;
    }
    return false;
}

/****************************************************************
* This is for checking if an operator matches the passed operator 
* string.
*****************************************************************/
bool Calculator::matchingOperator(char letter, std::string operators)
{
    if (operators.find(letter) != std::string::npos) {
        return true;
    }
    return false;
}

