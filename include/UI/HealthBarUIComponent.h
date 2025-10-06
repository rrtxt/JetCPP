#pragma once

#include "UIComponent.h"

class HealthBarUIComponent : public UIComponent {
public:
    HealthBarUIComponent(GameState* gameState);
    
    void Draw() override;

private:
    GameState* gameState;
    int maxHealth;
    
    // Visual properties
    Vector2 position;
    Vector2 size;
    Color healthColor;
    Color backgroundColor;
};
