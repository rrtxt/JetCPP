#pragma once

#include "Scene.h"
#include "Player.h"
#include "Spawner.h"
#include "CollisionSystem.h"
#include "UISystem.h"

class InGameScene : public Scene {
public:
    InGameScene(GameState* gameState, EventSystem* eventSystem);
    ~InGameScene() override = default;

    void Update() override;
    void Draw() override;
    void OnEnter() override;
    void OnExit() override;

private:
    // Game entities
    std::unique_ptr<Player> player;
    std::unique_ptr<Spawner> spawner;
    std::unique_ptr<UISystem> uiSystem;
    
    void InitializeGame();
    void UpdateGameLogic();
    void HandleGameOver();
};
