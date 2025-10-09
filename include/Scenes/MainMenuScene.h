#pragma once

#include "Scene.h"
#include "UISystem.h"
#include <memory>

class MainMenuScene : public Scene {
public:
    MainMenuScene(GameState* gameState, EventSystem* eventSystem);
    ~MainMenuScene() override = default;

    void Update() override;
    void Draw() override;
    void OnEnter(SoundSystem* soundSystem) override;
    void OnExit() override;

private:
    std::unique_ptr<UISystem> uiSystem;
};
