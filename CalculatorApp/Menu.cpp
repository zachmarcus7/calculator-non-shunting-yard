#include "Menu.h"


// menu constructor
Menu::Menu()
{
    this->calculator = Calculator();
}

// this is the prompt that gets shown when a user chooses to evaluate an expression
void Menu::evaluatePrompt()
{
    std::string input;
    std::cout << "Please enter your expression: " << std::endl;
    std::getline(std::cin, input);

    // output the expression
    std::cout << "The result of your expression is: " << this->calculator.evaluate(input) << std::endl;
}

// this is for validating the user's selection from the opening menu
int Menu::validate()
{
    int answer = 0;
    std::cin >> std::setw(1) >> answer;

    while ((!std::cin.good()) || ((!(answer == 1)) && (!(answer == 2))))
    {
        std::cout << "Invalid value entered." << std::endl;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Enter correct value:" << std::endl;
        //make sure only one integer is accepted
        std::cin >> std::setw(1) >> answer;
    }

    //clear the buffer
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    return answer;
}

// this provides the user with a menu to choose an option
bool Menu::run()
{
    // show opening prompt to user
    std::cout << "Please enter an option:" << std::endl;
    std::cout << "(1) Parse and evaluate expression" << std::endl;
    std::cout << "(2) Exit" << std::endl;

    // validate the user's selection
    int selection = validate();

    if (selection == 1)
    {
        this->evaluatePrompt();
        return true;
    }
    else
    {
        std::cout << "Goodbye!" << std::endl;
        return false;
    }
}
