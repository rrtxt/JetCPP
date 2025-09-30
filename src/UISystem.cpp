#include "UISystem.h"

UISystem::UISystem(GameState* gs) {
    isGameOver = false;
    gameState = gs;
}

void UISystem::Draw() {
    // TODO: Add placeholder for UI elements like health bar, score, etc.
    DrawText("Health: ", 10, 10, 20, BLACK);
    DrawText(TextFormat("Score : %i", gameState->score), 10, 40, 20, BLACK);
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
