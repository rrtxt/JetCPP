#pragma once

#include "Common.h"
#include "EventSystem.h"

class GameState {
public:
    // Scene state
    enum Scene {
        MAIN_MENU,
        IN_GAME,
    } scene = MAIN_MENU;
    int selectedMenuOption = 0;

    // Game state
    bool isGameOver;
    int score;

    // Player state
    int playerHealth;
    int playerCurrentHealth;

    GameState(bool isGameOver = false, int score = 0,int playerHealth = 3)
        : isGameOver(isGameOver), score(score), playerHealth(playerHealth), playerCurrentHealth(playerHealth) {}
    void RegisterEvents(EventSystem* es);
};
