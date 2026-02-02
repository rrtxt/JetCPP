#include "PauseMenuUIComponent.h"
#include "Common.h"
#include "raylib.h"

PauseMenuUIComponent::PauseMenuUIComponent(
    GameState* gameState,
    EventSystem* eventSystem
)
    : gameState(gameState),
      eventSystem(eventSystem) {

    titleFontSize = 40;
    optionFontSize = 20;

    titleColor = BLACK;
    optionColor = BLACK;
    backgroundColor = Fade(BLACK, 0.6f);

    // Hidden by default
    SetVisible(false);
}

void PauseMenuUIComponent::Update() {
    if (!isEnabled) return;

    // Pause state is derived from TimeScale
    bool paused = gameState->isPaused && !gameState->isGameOver;

    SetVisible(paused);

    if (paused) {
        HandleInput();
    }
}

void PauseMenuUIComponent::Draw() {
    if (!isVisible || !isEnabled) return;

    // Dark overlay
    DrawRectangle(
        0, 0,
        VIRTUAL_WIDTH,
        VIRTUAL_HEIGHT,
        backgroundColor
    );

    // Title
    const char* titleText = "PAUSED";
    int titleWidth = MeasureText(titleText, titleFontSize);

    int centerX = VIRTUAL_WIDTH / 2;
    int centerY = VIRTUAL_HEIGHT / 2;

    DrawText(
        titleText,
        centerX - titleWidth / 2,
        centerY - 80,
        titleFontSize,
        titleColor
    );

    // Options
    const char* resumeText = "ESC - Resume";
    const char* restartText = "R - Restart";
    const char* menuText = "M - Main Menu";

    DrawText(
        resumeText,
        centerX - MeasureText(resumeText, optionFontSize) / 2,
        centerY - 10,
        optionFontSize,
        optionColor
    );

    DrawText(
        restartText,
        centerX - MeasureText(restartText, optionFontSize) / 2,
        centerY + 20,
        optionFontSize,
        optionColor
    );

    DrawText(
        menuText,
        centerX - MeasureText(menuText, optionFontSize) / 2,
        centerY + 50,
        optionFontSize,
        optionColor
    );
}

void PauseMenuUIComponent::HandleInput() {
    // Restart
    if (IsKeyPressed(KEY_R)) {
        eventSystem->Emit("RestartGame");
    }

    // Back to main menu
    if (IsKeyPressed(KEY_M)) {
        eventSystem->Emit("ChangeToMainMenu");
    }
}
