#pragma once

#include "Common.h"
#include "EventSystem.h"

class GameState {
public:
    bool isGameOver = false;
    int score = 0;

    void RegisterEvents(EventSystem* es);
};
