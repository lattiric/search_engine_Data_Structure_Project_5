//
// Created by Rick Lattin on 5/2/21.
//

#ifndef SEARCH_ENGINE_UI_H
#define SEARCH_ENGINE_UI_H
#include <iostream>

class UI{
private:
    std::string arg;
    std::string userInput;
public:
    UI();
    UI(std::string);
    void askUser(); //uses user interface
};

#endif //SEARCH_ENGINE_UI_H
