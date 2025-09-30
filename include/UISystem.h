#pragma once

#include "Common.h"
#include "GameState.h"
#include "HealthBarUI.h"

class UISystem {
public:
    bool isGameOver;
    GameState* gameState;

    // UI Component
    HealthBarUI healthBar;

    UISystem(GameState* gs);
    void Draw();
};
