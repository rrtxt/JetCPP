#pragma once

#include "UIComponent.h"

class ScoreUIComponent : public UIComponent {
public:
    ScoreUIComponent(GameState* gameState);
    
    void Draw() override;

private:
    GameState* gameState;
    
    // Visual properties
    Vector2 position;
    int fontSize;
    Color textColor;
};
