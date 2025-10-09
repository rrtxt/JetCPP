#include "MainMenuScene.h"
#include "TimeScale.h"

MainMenuScene::MainMenuScene(GameState* gameState, EventSystem* eventSystem)
    : Scene(gameState, eventSystem) {
    
    // Create UI system for main menu
    uiSystem = std::make_unique<UISystem>(gameState, eventSystem);
    uiSystem->SetupMainMenuUI();
}

void MainMenuScene::Update() {
    // Update UI components (handles input automatically)
    if (uiSystem) {
        uiSystem->Update();
    }
}

void MainMenuScene::Draw() {
    // UI components handle their own drawing (including background)
    if (uiSystem) {
        uiSystem->Draw();
    }
}

void MainMenuScene::OnEnter(SoundSystem* soundSystem) {
    std::cout << "Entered Main Menu Scene" << std::endl;
    soundSystem = soundSystem;

    // Reset game state when entering main menu
    gameState->isGameOver = false;
    gameState->score = 0;
    gameState->playerCurrentHealth = gameState->playerHealth;
    gameState->selectedMenuOption = 0;
    
    // Reset time scale
    TimeScale::Set(1);
}

void MainMenuScene::OnExit() {
    std::cout << "Exited Main Menu Scene" << std::endl;
}
