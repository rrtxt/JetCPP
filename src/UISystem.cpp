#include "UISystem.h"
#include "HealthBarUI.h"

UISystem::UISystem(GameState* gs)
    : gameState(gs),
      healthBar(gs->playerHealth)
{
    isGameOver = false;
}

void UISystem::Draw() {
    // TODO: Add placeholder for UI elements like health bar, score, etc.
    healthBar.Draw(gameState->playerCurrentHealth);
    const char* scoreMsg = TextFormat("%i", gameState->score);
    int scoreMsgWidth = MeasureText(scoreMsg, 30);
    DrawText(scoreMsg, GetScreenWidth() / 2 - scoreMsgWidth / 2, 30, 30, BLACK);
    isGameOver = gameState->isGameOver;

    if(isGameOver) {
        const char* msg = "GAME OVER!";
        int fontSize = 40;
        int textWidth = MeasureText(msg, fontSize);
        DrawText(msg,
            GetScreenWidth()/2 - textWidth/2,
            GetScreenHeight()/2 - fontSize/2,
            fontSize, BLACK);
    }
}
