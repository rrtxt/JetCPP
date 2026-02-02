#include "InGameScene.h"
#include "CameraSystem.h"
#include "Common.h"
#include "GameState.h"
#include "SoundSystem.h"
#include "Spawner.h"
#include "TimeScale.h"
#include "Enemy/EnemyTypes.h"
#include "CollisionSystem.h"
#include <memory>
#include <raylib.h>
#include <vector>
#define ASSERT_PTR(x) if (!(x)) { TraceLog(LOG_ERROR, #x " is NULL"); return; }

InGameScene::InGameScene(GameState* gameState, EventSystem* eventSystem, CameraSystem* cameraSystem)
    : cameraSystem(cameraSystem), Scene(gameState, eventSystem) {
    // InitializeGame();
}

void InGameScene::Update() {
    if (!gameState->isGameOver) {
        // waveSystem->Update();
        UpdateGameLogic();

        // Check if all waves are completed (victory condition)
        if (waveSystem && waveSystem->IsWaveFinished()) {
            std::cout << "All waves completed! Victory!" << std::endl;
        }
    }

    // Update UI components
    if (uiSystem) {
        uiSystem->Update();
    }

    if (cameraSystem){
        cameraSystem->Update();
    }
}

void InGameScene::Draw() {
    if (!gameState->isGameOver) {
        // Draw game entities
        if (player) player->Draw();
        if (waveSystem) waveSystem->Draw();
    }

    // Always draw UI
    if (uiSystem) uiSystem->Draw();
}

void InGameScene::OnEnter(SoundSystem* soundSystem) {
    // ASSERT_PTR(gameState);
    // ASSERT_PTR(eventSystem);
    // ASSERT_PTR(cameraSystem);
    // ASSERT_PTR(player);
    // ASSERT_PTR(soundSystem);
    std::cout << "Entered In-Game Scene" << std::endl;

    // Sound initialization
    this->soundSystem = soundSystem;
    this->soundSystem->LoadSFX("shoot", "assets/sound/BulletShoot.wav");
    this->soundSystem->LoadSFX("explosion", "assets/sound/Explosion.wav");
    this->soundSystem->LoadSFX("player_hit", "assets/sound/PlayerHit.wav");

    // Reset time scale
    TimeScale::Set(1);

    // Reset game state
    gameState->isPaused = false;
    gameState->isGameOver = false;
    gameState->score = 0;
    gameState->playerCurrentHealth = gameState->playerHealth;

    // Reinitialize game if needed
    if (!player || !waveSystem) {
        InitializeGame();
    } else {
        // Reset existing entities
        player->currentHealth = player->maxHealth;
        player->position = {VIRTUAL_WIDTH / 2.0f - player->size.x / 2.0f, VIRTUAL_HEIGHT / 2.0f};
        player->bullets.clear();

        // Reset all spawners before restarting waves
        if (normalSpawner) normalSpawner->Reset();
        if (zigzagSpawner) zigzagSpawner->Reset();

        // Reset and start the wave system
        waveSystem->Reset();
        waveSystem->Start();
    }
}

void InGameScene::OnExit() {
    std::cout << "Exited In-Game Scene" << std::endl;
    soundSystem->StopMusic();
    soundSystem->UnloadSFX("shoot");
    soundSystem->UnloadSFX("player_hit");
    soundSystem->UnloadSFX("explosion");
    // Keep entities alive for potential return to game
}

void InGameScene::InitializeGame() {
    // Create game entities with settings applied
    player = std::make_unique<Player>(VIRTUAL_WIDTH / 2, VIRTUAL_HEIGHT / 2, eventSystem);
    normalSpawner = std::make_unique<Spawner>(VIRTUAL_WIDTH / 2 - 15, -30, EnemyType::NORMAL, eventSystem, gameState);
    zigzagSpawner = std::make_unique<Spawner>(VIRTUAL_WIDTH / 2 - 15, -30, EnemyType::ZIGZAG, eventSystem, gameState);

    waveSystem = std::make_unique<GamewaveSystem>(gameState, normalSpawner.get(), zigzagSpawner.get());
    uiSystem = std::make_unique<UISystem>(gameState, eventSystem);

    // Apply game settings to entities
    ApplyGameSettings();

    // Setup in-game UI components
    uiSystem->SetupInGameUI();

    player->Start();
    std::cout << "Game initialized with settings applied - Player at: " << player->position.x << ", " << player->position.y << std::endl;
    waveSystem->Start();
}

void InGameScene::UpdateGameLogic() {
    // Update game entities
    if (player) player->Update();
    if (waveSystem) waveSystem->Update();

    // Handle Key
    if (IsKeyPressed(KEY_ESCAPE)){
        TimeScale::Set(gameState->isPaused);
        gameState->isPaused = !gameState->isPaused;
    }

    if (!waveSystem) return;

    // Check collisions
    auto currentWave = waveSystem->GetCurrentWave();
    if (!currentWave) return;

    const auto& currentSpawners = currentWave->GetSpawners();
    if (currentSpawners.empty()) return;

    for (auto& spawner : currentSpawners){
        CollisionSystem::CheckCollisionPlayerEnemy(*player, spawner->enemies);
        CollisionSystem::CheckCollisionBulletEnemy(player->bullets, spawner->enemies);
    }
}

void InGameScene::ApplyGameSettings() {
    if (!player) return;

    const GameSettings& settings = gameState->settings;

    // Apply difficulty settings to player
    player->maxHealth = settings.GetPlayerStartingHealth();
    player->currentHealth = player->maxHealth;

    std::cout << "Applied game settings:" << std::endl;
    std::cout << "  Difficulty: " << (settings.difficulty == GameSettings::EASY ? "Easy" :
                                     settings.difficulty == GameSettings::NORMAL ? "Normal" : "Hard") << std::endl;
    std::cout << "  Player Health: " << player->maxHealth << std::endl;
    std::cout << "  Enemy Speed Multiplier: " << settings.GetEnemySpeedMultiplier() << std::endl;
    std::cout << "  Control Scheme: " << (settings.controlScheme == GameSettings::WASD ? "WASD" : "Arrow Keys") << std::endl;
    std::cout << "  Master Volume: " << (settings.masterVolume * 100) << "%" << std::endl;
}
