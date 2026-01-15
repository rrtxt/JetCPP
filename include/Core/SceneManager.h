#pragma once

#include "Common.h"
#include "GameState.h"
#include "EventSystem.h"
#include "SoundSystem.h"

// Forward declarations
class Scene;

class SceneManager {
public:
    SceneManager(GameState* gameState, EventSystem* eventSystem, SoundSystem* soundSystem, CameraSystem* cameraSystem);
    ~SceneManager();

    // Scene management
    void ChangeScene(GameState::Scene newScene);
    void Update();
    void Draw();

    // Getters
    GameState::Scene GetCurrentScene() const { return currentScene; }
    Scene* GetCurrentSceneObject() const { return currentSceneObject; }

private:
    GameState* gameState;
    EventSystem* eventSystem;
    SoundSystem* soundSystem;
    CameraSystem* cameraSystem;
    GameState::Scene currentScene;
    GameState::Scene pendingScene;
    bool hasPendingsSceneChange = false;
    Scene* currentSceneObject;

    // Scene creation
    Scene* CreateScene(GameState::Scene sceneType);
    void ApplySceneChange();
    void CleanupCurrentScene();
};
