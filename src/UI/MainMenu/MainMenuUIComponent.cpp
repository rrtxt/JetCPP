#include "MainMenuUIComponent.h"

MainMenuUIComponent::MainMenuUIComponent(GameState* gameState, EventSystem* eventSystem) 
    : gameState(gameState), eventSystem(eventSystem) {
    
    // Set up visual properties
    titleFontSize = 60;
    optionFontSize = 20;
    optionSpacing = 50;
    titleColor = BLACK;
    selectedColor = RED;
    normalColor = BLACK;
    instructionColor = LIGHTGRAY;
}

void MainMenuUIComponent::Draw() {
    if (!isVisible || !isEnabled) return;
    
    // Draw background
    ClearBackground(WHITE);
    
    // Draw title
    const char* title = "JET GAME";
    int titleWidth = MeasureText(title, titleFontSize);
    titlePosition.x = GetScreenWidth() / 2 - titleWidth / 2;
    titlePosition.y = GetScreenHeight() / 4;
    
    DrawText(title, titlePosition.x, titlePosition.y, titleFontSize, titleColor);
    
    // Draw menu options
    int totalMenuHeight = options.size() * optionSpacing;
    menuStartPosition.x = GetScreenWidth() / 2;
    menuStartPosition.y = GetScreenHeight() / 2 - totalMenuHeight / 2;
    
    for (int i = 0; i < options.size(); i++) {
        Color color = (i == gameState->selectedMenuOption) ? selectedColor : normalColor;
        const char* optionText = options[i].c_str();
        int optionWidth = MeasureText(optionText, optionFontSize);
        
        DrawText(optionText, 
            menuStartPosition.x - optionWidth / 2, 
            menuStartPosition.y + i * optionSpacing, 
            optionFontSize, color);
    }
    
    // Draw instructions
    const char* instruction = "Use UP/DOWN arrows to navigate, ENTER to select";
    int instrWidth = MeasureText(instruction, 16);
    DrawText(instruction,
        GetScreenWidth() / 2 - instrWidth / 2,
        GetScreenHeight() - 50,
        16, instructionColor);
}

void MainMenuUIComponent::Update() {
    if (!isEnabled) return;
    
    HandleInput();
}

void MainMenuUIComponent::HandleInput() {
    // Navigate menu options
    if (IsKeyPressed(KEY_UP)) {
        gameState->selectedMenuOption--;
        if (gameState->selectedMenuOption < 0) {
            gameState->selectedMenuOption = options.size() - 1;
        }
    }
    
    if (IsKeyPressed(KEY_DOWN)) {
        gameState->selectedMenuOption++;
        if (gameState->selectedMenuOption >= options.size()) {
            gameState->selectedMenuOption = 0;
        }
    }
    
    // Select menu option
    if (IsKeyPressed(KEY_ENTER)) {
        HandleMenuSelection();
    }
}

void MainMenuUIComponent::HandleMenuSelection() {
    switch (gameState->selectedMenuOption) {
        case 0: // Start Game
            eventSystem->Emit("ChangeToInGame");
            break;
        case 1: // Settings
            eventSystem->Emit("ChangeToSettings");
            break;
        case 2: // Exit
            std::cout << "Exit selected" << std::endl;
            // Note: Window closing is handled by main loop
            break;
        default:
            break;
    }
}
