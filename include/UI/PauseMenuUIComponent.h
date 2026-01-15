
#pragma once

#include "UIComponent.h"

class PauseMenuUIComponent : public UIComponent {
public:
    PauseMenuUIComponent(GameState* gameState, EventSystem* eventSystem);

    void Draw() override;
    void Update() override;

private:
    GameState* gameState;
    EventSystem* eventSystem;

    // Visual properties
    int titleFontSize;
    int optionFontSize;
    Color titleColor;
    Color optionColor;
    Color backgroundColor;

    void HandleInput();
};
