#pragma once

#include "Common.h"

class MainMenuUI{
public:
    std::vector<string> options = {"Start Game", "Options", "Exit"};
    int selectedOption;
    MainMenuUI(int selectedOption = 0);
    void Draw(int selectedOption);
};