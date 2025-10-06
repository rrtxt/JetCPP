#include "GameState.h"

// GameSettings implementations
float GameSettings::GetEnemySpeedMultiplier() const {
    switch (difficulty) {
        case EASY: return 0.7f;
        case NORMAL: return 1.0f;
        case HARD: return 1.5f;
        default: return 1.0f;
    }
}

int GameSettings::GetPlayerStartingHealth() const {
    switch (difficulty) {
        case EASY: return 5;
        case NORMAL: return 3;
        case HARD: return 1;
        default: return 3;
    }
}

float GameSettings::GetSpawnRateMultiplier() const {
    switch (difficulty) {
        case EASY: return 0.5f;
        case NORMAL: return 1.0f;
        case HARD: return 1.25f;
        default: return 0.5f;
    }
}

// GameState implementations
GameState::GameState(bool isGameOver, int score, int playerHealth)
    : isGameOver(isGameOver), score(score), playerHealth(playerHealth), playerCurrentHealth(playerHealth) {
    // Initialize player health based on difficulty setting
    this->playerHealth = settings.GetPlayerStartingHealth();
    this->playerCurrentHealth = this->playerHealth;
}

void GameState::ApplySettings(const GameSettings& newSettings) {
    settings = newSettings;
    // Update player health if difficulty changed
    playerHealth = settings.GetPlayerStartingHealth();
    if (playerCurrentHealth > playerHealth) {
        playerCurrentHealth = playerHealth;
    }
}

void GameState::ResetGameForNewSettings() {
    // Reset game state when settings change
    isGameOver = false;
    score = 0;
    playerHealth = settings.GetPlayerStartingHealth();
    playerCurrentHealth = playerHealth;
}

void GameState::RegisterEvents(EventSystem* es) {
    es->Subscribe("OnPlayerDied", [&]() {
        this->isGameOver = true;
    });
    es->Subscribe("OnPlayerHit", [&, es]() {
        this->playerCurrentHealth -= 1;
        cout << "Player Health: " << this->playerCurrentHealth << endl;

        es->Emit("OnHealthchanged");
    });
    es->Subscribe("OnHealthchanged", [&, es](){
        if(this->playerCurrentHealth <= 0){
            es->Emit("OnPlayerDied");
        }
    });
    es->Subscribe("OnEnemyDestroyed", [&]() {
        this->score += 100;
    });
}
