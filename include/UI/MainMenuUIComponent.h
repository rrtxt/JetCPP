#pragma once

#include "UIComponent.h"
#include "EventSystem.h"

class MainMenuUIComponent : public UIComponent {
public:
    MainMenuUIComponent(GameState* gameState, EventSystem* eventSystem);
    
    void Draw() override;
    void Update() override;

private:
    GameState* gameState;
    EventSystem* eventSystem;
    
    // Menu options
    std::vector<std::string> options = {"Start Game", "Options", "Exit"};
    
    // Visual properties
    Vector2 titlePosition;
    Vector2 menuStartPosition;
    int titleFontSize;
    int optionFontSize;
    int optionSpacing;
    Color titleColor;
    Color selectedColor;
    Color normalColor;
    Color instructionColor;
    
    void HandleInput();
    void HandleMenuSelection();
};
