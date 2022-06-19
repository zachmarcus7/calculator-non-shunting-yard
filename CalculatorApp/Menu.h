#include <iostream>
#include <iomanip>
#include "Calculator.h"

#ifndef MENU_H
#define MENU_H

class Menu
{
private:
    Calculator calculator;

public:
    Menu();
    void evaluatePrompt();
    int validate();
    bool run();
};
#endif
