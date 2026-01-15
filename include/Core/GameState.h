#pragma once

#include "Common.h"
#include "EventSystem.h"
#include "SoundSystem.h"
#include "CameraSystem.h"
#include "TimeScale.h"

// Game settings structure
struct GameSettings {
    // Audio settings
    float masterVolume = 0.7f;
    float sfxVolume = 0.8f;
    float musicVolume = 0.6f;

    // Gameplay settings
    enum Difficulty { EASY = 0, NORMAL = 1, HARD = 2 } difficulty = NORMAL;
    enum ControlScheme { WASD = 0, ARROW_KEYS = 1 } controlScheme = WASD;

    // Graphics settings
    enum GraphicsQuality { LOW = 0, MEDIUM = 1, HIGH = 2 } graphicsQuality = MEDIUM;
    bool fullscreen = false;
    bool vsync = true;

    // Gameplay modifiers based on difficulty
    float GetEnemySpeedMultiplier() const;
    int GetPlayerStartingHealth() const;
    float GetSpawnRateMultiplier() const;
    float GetEnemyMaxSpawnCount() const;
    float GetEnemySpawnSpread() const;
};

class GameState {
public:
    // Scene state
    enum Scene {
        MAIN_MENU,
        IN_GAME,
        SETTINGS,
    } scene = MAIN_MENU;
    int selectedMenuOption = 0;

    // Game state
    bool isShouldQuit = false;
    bool isGameOver;
    bool isPaused = false;
    int score;

    // Player state
    int playerHealth;
    int playerCurrentHealth;

    // Game settings
    GameSettings settings;

    GameState(bool isGameOver = false, int score = 0, int playerHealth = 3);

    void RegisterEvents(EventSystem* eventSystem, SoundSystem* soundSystem);

    // Settings management
    void ApplySettings(const GameSettings& newSettings);
    void ResetGameForNewSettings();
};
