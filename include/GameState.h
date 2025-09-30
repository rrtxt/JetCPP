#pragma once

#include "Common.h"
#include "EventSystem.h"

class GameState {
public:
    bool isGameOver;
    int score;

    // Player state
    int playerHealth;
    int playerCurrentHealth ;

    GameState(bool isGameOver = false, int score = 0,int playerHealth = 3)
        : isGameOver(isGameOver), score(score), playerHealth(playerHealth), playerCurrentHealth(playerHealth) {}
    void RegisterEvents(EventSystem* es);
};
