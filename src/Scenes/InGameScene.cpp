#include "InGameScene.h"
#include "TimeScale.h"

InGameScene::InGameScene(GameState* gameState, EventSystem* eventSystem)
    : Scene(gameState, eventSystem) {
    InitializeGame();
}

void InGameScene::Update() {
    if (!gameState->isGameOver) {
        UpdateGameLogic();
    } else {
        HandleGameOver();
    }
    
    // Update UI components
    if (uiSystem) {
        uiSystem->Update();
    }
}

void InGameScene::Draw() {
    ClearBackground(RAYWHITE);
    
    if (!gameState->isGameOver) {
        // Draw game entities
        if (player) player->Draw();
        if (spawner) spawner->Draw();
    }
    
    // Always draw UI (includes game over screen)
    if (uiSystem) uiSystem->Draw();
}

void InGameScene::OnEnter() {
    std::cout << "Entered In-Game Scene" << std::endl;
    
    // Reset time scale
    TimeScale::Set(1);
    
    // Reset game state
    gameState->isGameOver = false;
    gameState->score = 0;
    gameState->playerCurrentHealth = gameState->playerHealth;
    
    // Reinitialize game if needed
    if (!player || !spawner) {
        InitializeGame();
    } else {
        // Reset existing entities
        player->currentHealth = player->maxHealth;
        player->position = {GetScreenWidth() / 2.0f - player->size.x / 2.0f, GetScreenHeight() / 2.0f};
        player->bullets.clear();
        spawner->enemies.clear();
        spawner->spawnCount = 0;
    }
}

void InGameScene::OnExit() {
    std::cout << "Exited In-Game Scene" << std::endl;
    // Keep entities alive for potential return to game
}

void InGameScene::InitializeGame() {
    // Create game entities
    player = std::make_unique<Player>(25, 40, GetScreenWidth() / 2, GetScreenHeight() / 2, eventSystem);
    spawner = std::make_unique<Spawner>(GetScreenWidth() / 2 - 15, -30, eventSystem);
    uiSystem = std::make_unique<UISystem>(gameState, eventSystem);
    
    // Setup in-game UI components
    uiSystem->SetupInGameUI();
    
    std::cout << "Game initialized - Player at: " << player->position.x << ", " << player->position.y << std::endl;
}

void InGameScene::UpdateGameLogic() {
    // Update game entities
    if (player) player->Update();
    if (spawner) spawner->Update();
    
    // Check collisions
    if (player && spawner) {
        CollisionSystem::CheckCollisionPlayerEnemy(*player, spawner->enemies);
        CollisionSystem::CheckCollisionBulletEnemy(player->bullets, spawner->enemies);
    }
}

void InGameScene::HandleGameOver() {
    // Restart game
    if (IsKeyPressed(KEY_R)) {
        OnEnter();
    }
    
    if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_ESCAPE)) {
        // Return to main menu
        eventSystem->Emit("ChangeToMainMenu");
    }
}
