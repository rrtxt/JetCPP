#include "SettingsScene.h"

SettingsScene::SettingsScene(GameState* gameState, EventSystem* eventSystem) : Scene(gameState, eventSystem) {
    uiSystem = std::make_unique<UISystem>(gameState, eventSystem);
    uiSystem->SetupSettingsUI();
}

void SettingsScene::Update() {
    if (uiSystem) {
        uiSystem->Update();
    }
}

void SettingsScene::Draw() {
    if (uiSystem) {
        uiSystem->Draw(); 
    }
}

void SettingsScene::OnEnter(SoundSystem* soundSystem) {
    std::cout << "Entered Settings Scene" << std::endl;
    this->soundSystem = soundSystem;

}

void SettingsScene::OnExit() {
    std::cout << "Exited Settings Scene" << std::endl;
}