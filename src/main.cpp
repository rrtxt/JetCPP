#include "Common.h"
#include "Events/GameStateEvents.h"
#include "GameSceneEvents.h"
#include "GameState.h"
#include "EventSystem.h"
#include "SoundSystem.h"
#include "CameraSystem.h"
#include "SceneManager.h"
#include <raylib.h>

int main() {
    InitWindow(600, 900, "Jet Game");
    SetExitKey(KEY_NULL);
    InitAudioDevice();

    SetTargetFPS(60);

    // Initialize camer
    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0.0f, 0.0f };
    camera.offset = (Vector2){ 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Initialize core systems
    GameState gameState;
    EventSystem eventSystem;
    SoundSystem soundSystem;
    CameraSystem cameraSystem(&camera, &eventSystem);
    soundSystem.SetVolume(gameState.settings.masterVolume);

    // Initialize scene manager
    SceneManager sceneManager(&gameState, &eventSystem, &soundSystem, &cameraSystem);

    // Register game state events
    // gameState.RegisterEvents(&eventSystem, &soundSystem);
    GameStateEvents::Register(&eventSystem, &gameState, &soundSystem);
    GameSceneEvents::Register(&eventSystem, &sceneManager, &gameState);


    std::cout << "Game initialized with Scene Manager" << std::endl;

    while (!WindowShouldClose() && !gameState.isShouldQuit) {
        // Update current scene
        sceneManager.Update();

        // Render current scene
        BeginDrawing();
            BeginMode2D(camera);
                sceneManager.Draw();
            EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
