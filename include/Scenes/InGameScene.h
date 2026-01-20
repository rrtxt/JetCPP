#pragma once

#include "CameraSystem.h"
#include "Scene.h"
#include "Player.h"
#include "Spawner.h"
#include "GamewaveSystem.h"
#include "UISystem.h"
#include <memory>

class InGameScene : public Scene {
public:
    InGameScene(GameState* gameState, EventSystem* eventSystem, CameraSystem* cameraSystem);
    ~InGameScene() override = default;

    void Update() override;
    void Draw() override;
    void OnEnter(SoundSystem* soundsystem) override;
    void OnExit() override;

private:
    CameraSystem* cameraSystem;

    // Game entities
    std::unique_ptr<Player> player;
    std::unique_ptr<Spawner> normalSpawner;
    std::unique_ptr<Spawner> zigzagSpawner;
    std::unique_ptr<GamewaveSystem> waveSystem;
    std::unique_ptr<UISystem> uiSystem;

    void InitializeGame();
    void UpdateGameLogic();
    // void HandleGameOver();
    void ApplyGameSettings();
};
