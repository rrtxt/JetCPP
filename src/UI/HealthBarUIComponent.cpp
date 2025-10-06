#include "HealthBarUIComponent.h"

HealthBarUIComponent::HealthBarUIComponent(GameState* gameState) 
    : gameState(gameState), maxHealth(gameState->playerHealth) {
    
    // Set up visual properties
    position = {20, 20};
    size = {200, 20};
    healthColor = GREEN;
    backgroundColor = DARKGRAY;
}

void HealthBarUIComponent::Draw() {
    if (!isVisible || !isEnabled) return;
    
    for (int i = 0; i < this->maxHealth; i++){
        if (i < this->gameState->playerCurrentHealth){
            DrawRectangle(20 + i * 35, 20, 30, 30, BLACK);
        } else {
            DrawRectangle(20 + i * 35, 20, 30, 30, GRAY);
        }
    }
}
