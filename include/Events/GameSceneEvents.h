#pragma once

#include "EventSystem.h"
#include "GameState.h"
#include "SceneManager.h"

class GameSceneEvents {
  public:
    static void Register(EventSystem* eventSystem, SceneManager* sceneManager, GameState* gameState);
};
