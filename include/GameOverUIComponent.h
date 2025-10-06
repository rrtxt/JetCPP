#pragma once

#include "UIComponent.h"

class GameOverUIComponent : public UIComponent {
public:
    GameOverUIComponent(GameState* gameState, EventSystem* eventSystem);
    
    void Draw() override;
    void Update() override;

private:
    GameState* gameState;
    EventSystem* eventSystem;
    
    // Visual properties
    Vector2 titlePosition;
    Vector2 instructionPosition;
    int titleFontSize;
    int instructionFontSize;
    Color titleColor;
    Color instructionColor;
    
    void HandleInput();
};
