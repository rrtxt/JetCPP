#include "SceneManager.h"
#include "GameState.h"
#include "Scene.h"
#include "MainMenuScene.h"
#include "InGameScene.h"
#include "SettingsScene.h"
#include "TimeScale.h"

SceneManager::SceneManager(GameState* gameState, EventSystem* eventSystem, SoundSystem* soundSystem, CameraSystem* cameraSystem)
    : gameState(gameState), eventSystem(eventSystem), soundSystem(soundSystem), cameraSystem(cameraSystem), currentScene(GameState::MAIN_MENU), currentSceneObject(nullptr) {

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
        this->gameState->isPaused = false;
        this->gameState->isGameOver = false;
        this->gameState->score = 0;
        this->gameState->playerCurrentHealth = this->gameState->playerHealth;
        TimeScale::Set(1);
        ChangeScene(GameState::IN_GAME);
    });

    // Initialize with main menu
    ChangeScene(GameState::MAIN_MENU);
}

SceneManager::~SceneManager() {
    CleanupCurrentScene();
}

void SceneManager::ChangeScene(GameState::Scene newScene) {
    pendingScene = newScene;
    hasPendingsSceneChange = true;
    std::cout << "Scene changed to: " << (newScene == GameState::MAIN_MENU ? "MAIN_MENU" : "IN_GAME") << std::endl;
}

void SceneManager::Update() {
    if (currentSceneObject) {
        currentSceneObject->Update();
    }

    ApplySceneChange();
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
            return new InGameScene(gameState, eventSystem, cameraSystem);
        case GameState::SETTINGS:
            return new SettingsScene(gameState, eventSystem);
        default:
            std::cout << "Warning: Unknown scene type!" << std::endl;
            return nullptr;
    }
}

void SceneManager::ApplySceneChange(){
    if (!hasPendingsSceneChange) return;

    if (currentSceneObject) {
        currentSceneObject->OnExit();
        delete currentSceneObject;
        currentSceneObject = nullptr;
    }

    currentScene = pendingScene;
    gameState->scene = pendingScene;

    currentSceneObject = CreateScene(pendingScene);

    if (currentSceneObject){
        currentSceneObject->OnEnter(soundSystem);
    }

    hasPendingsSceneChange = false;

    std::cout << "Scene changed to: " << (pendingScene == GameState::MAIN_MENU ? "MAIN_MENU" : "IN_GAME") << std::endl;
}

void SceneManager::CleanupCurrentScene() {
    if (currentSceneObject) {
        delete currentSceneObject;
        currentSceneObject = nullptr;
    }
}
