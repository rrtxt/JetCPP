#pragma once

#include "Common.h"
#include "GameState.h"
#include "EventSystem.h"

// Base Scene class for polymorphic scene handling
class Scene {
public:
    Scene(GameState* gameState, EventSystem* eventSystem) 
        : gameState(gameState), eventSystem(eventSystem) {}
    
    virtual ~Scene() = default;
    
    // Pure virtual methods that each scene must implement
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void OnEnter() {}  // Called when scene becomes active
    virtual void OnExit() {}   // Called when scene becomes inactive

protected:
    GameState* gameState;
    EventSystem* eventSystem;
};
