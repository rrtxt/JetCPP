#pragma once

#include "EventSystem.h"
#include "GameState.h"
#include "SoundSystem.h"

class GameStateEvents {
    public:
        static void Register(EventSystem* events, GameState* gameState, SoundSystem* soundSystem);
};
