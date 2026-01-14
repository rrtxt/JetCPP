#include "SceneManager.h"
#include "Scene.h"
#include "MainMenuScene.h"
#include "InGameScene.h"
#include "SettingsScene.h"
#include "TimeScale.h"

SceneManager::SceneManager(GameState* gameState, EventSystem* eventSystem, SoundSystem* soundSystem)
    : gameState(gameState), eventSystem(eventSystem), soundSystem(soundSystem), currentScene(GameState::MAIN_MENU), currentSceneObject(nullptr) {

    // Register scene change events
    eventSystem->Subscribe("ChangeToMainMenu", [this]() {
        ChangeScene(GameState::MAIN_MENU);
    });

    eventSystem->Subscribe("ChangeToInGame", [this]() {
        ChangeScene(GameState::IN_GAME);
    });

    eventSystem->Subscribe("ChangeToSettings", [this]() {
        ChangeScene(GameState::SETTINGS);
    });

    eventSystem->Subscribe("QuitGame", [&]() {
        this->gameState->isShouldQuit = true;
    });

    eventSystem->Subscribe("RestartGame", [this]() {
        // Reset game state and restart
        this->gameState->isGameOver = false;
        this->gameState->score = 0;
        this->gameState->playerCurrentHealth = this->gameState->playerHealth;
        TimeScale::Set(1);
        ChangeScene(GameState::IN_GAME);
    });

    eventSystem->Subscribe("OnPlayerDied", [this]() {
        // Reset time scale when player dies
        TimeScale::Set(0);
    });

    // Initialize with main menu
    ChangeScene(GameState::MAIN_MENU);
}

SceneManager::~SceneManager() {
    CleanupCurrentScene();
}

void SceneManager::ChangeScene(GameState::Scene newScene) {
    if (currentScene == newScene && currentSceneObject != nullptr) {
        return; // Already in this scene
    }

    // Exit current scene
    if (currentSceneObject) {
        currentSceneObject->OnExit();
    }

    CleanupCurrentScene();

    // Update game state
    currentScene = newScene;
    gameState->scene = newScene;

    // Create new scene
    currentSceneObject = CreateScene(newScene);

    // Enter new scene
    if (currentSceneObject) {
        currentSceneObject->OnEnter(soundSystem);
    }

    std::cout << "Scene changed to: " << (newScene == GameState::MAIN_MENU ? "MAIN_MENU" : "IN_GAME") << std::endl;
}

void SceneManager::Update() {
    if (currentSceneObject) {
        currentSceneObject->Update();
    }
}

void SceneManager::Draw() {
    if (currentSceneObject) {
        currentSceneObject->Draw();
    }
}

Scene* SceneManager::CreateScene(GameState::Scene sceneType) {
    switch (sceneType) {
        case GameState::MAIN_MENU:
            return new MainMenuScene(gameState, eventSystem);
        case GameState::IN_GAME:
            return new InGameScene(gameState, eventSystem);
        case GameState::SETTINGS:
            return new SettingsScene(gameState, eventSystem);
        default:
            std::cout << "Warning: Unknown scene type!" << std::endl;
            return nullptr;
    }
}

void SceneManager::CleanupCurrentScene() {
    if (currentSceneObject) {
        delete currentSceneObject;
        currentSceneObject = nullptr;
    }
}
