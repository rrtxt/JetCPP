#pragma once

#include "Scene.h"
#include "UISystem.h"

class SettingsScene : public Scene {
public:
    SettingsScene(GameState* gameState, EventSystem* eventSystem);
    void Update() override;
    void Draw() override;
    void OnEnter() override;
    void OnExit() override;
private:
    GameState* gameState;
    EventSystem* eventSystem;
    std::unique_ptr<UISystem> uiSystem;
};