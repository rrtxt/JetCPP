#include "ScoreUIComponent.h"

ScoreUIComponent::ScoreUIComponent(GameState* gameState) 
    : gameState(gameState) {
    
    // Set up visual properties
    fontSize = 30;
    textColor = BLACK;
}

void ScoreUIComponent::Draw() {
    if (!isVisible || !isEnabled) return;
    
    // Create score text
    const char* scoreText = TextFormat("%d", this->gameState->score);
    
    // Calculate centered position
    int textWidth = MeasureText(scoreText, fontSize);
    position.x = GetScreenWidth() / 2 - textWidth / 2;
    position.y = 30;
    
    // Draw score
    DrawText(scoreText, position.x, position.y, fontSize, textColor);
}
