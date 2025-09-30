#pragma once

#include "Common.h"
#include "GameState.h"

class UISystem {
public:
    bool isGameOver;
    GameState* gameState;

    UISystem(GameState* gs);
    void Draw();
};
