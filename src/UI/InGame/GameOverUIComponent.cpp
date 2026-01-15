#include "GameOverUIComponent.h"

GameOverUIComponent::GameOverUIComponent(GameState* gameState, EventSystem* eventSystem)
    : gameState(gameState), eventSystem(eventSystem) {

    // Set up visual properties
    titleFontSize = 40;
    instructionFontSize = 20;
    titleColor = BLACK;
    instructionColor = DARKGRAY;

    // Initially hidden - only show when game is over
    SetVisible(false);
}

void GameOverUIComponent::Draw() {
    if (!isVisible || !isEnabled || !gameState->isGameOver) return;

    // Calculate positions
    const char* titleText = "GAME OVER!";
    int titleWidth = MeasureText(titleText, titleFontSize);
    titlePosition.x = GetScreenWidth() / 2 - titleWidth / 2;
    titlePosition.y = GetScreenHeight() / 2 - titleFontSize / 2;

    const char* instructionText = "Press R to Restart or M/ESC for Main Menu";
    int instructionWidth = MeasureText(instructionText, instructionFontSize);
    instructionPosition.x = GetScreenWidth() / 2 - instructionWidth / 2;
    instructionPosition.y = titlePosition.y + titleFontSize + 20;

    // Draw game over text
    DrawText(titleText, titlePosition.x, titlePosition.y, titleFontSize, titleColor);

    // Draw instructions
    DrawText(instructionText, instructionPosition.x, instructionPosition.y, instructionFontSize, instructionColor);

    // Draw final score
    const char* finalScoreText = TextFormat("Final Score: %d", gameState->score);
    int finalScoreWidth = MeasureText(finalScoreText, 24);
    DrawText(finalScoreText,
        GetScreenWidth() / 2 - finalScoreWidth / 2,
        instructionPosition.y + instructionFontSize + 20,
        24, titleColor);
}

void GameOverUIComponent::Update() {
    if (!isEnabled) return;

    // Show/hide based on game state
    SetVisible(gameState->isGameOver);

    if (gameState->isGameOver) {
        HandleInput();
    }
}

void GameOverUIComponent::HandleInput() {
    // Restart game
    if (IsKeyPressed(KEY_R)) {
        eventSystem->Emit("RestartGame");
    }

    // Back to Main Menu
    if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_ESCAPE)) {
        eventSystem->Emit("ChangeToMainMenu");
    }
}
