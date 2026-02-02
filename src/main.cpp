#include "Common.h"
#include "Events/GameStateEvents.h"
#include "GameSceneEvents.h"
#include "GameState.h"
#include "EventSystem.h"
#include "SoundSystem.h"
#include "CameraSystem.h"
#include "SceneManager.h"
#include <cmath>
#include <raylib.h>

int main() {
    InitWindow(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, "Jet Game");
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

    // Set virtual viewport
    RenderTexture2D worldTarget = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

    std::cout << "Game initialized with Scene Manager" << std::endl;

    while (!WindowShouldClose() && !gameState.isShouldQuit) {
        // Update current scene
        sceneManager.Update();

        // Render current scene
        BeginTextureMode(worldTarget);
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
                sceneManager.Draw();
            EndMode2D();
        EndTextureMode();

        float scale = fmin(
            (float)GetScreenWidth() / VIRTUAL_WIDTH,
            (float)GetScreenHeight() / VIRTUAL_HEIGHT
        );

        Rectangle source = {
            0, 0,
            (float)worldTarget.texture.width,
            -(float)worldTarget.texture.height
        };

        Rectangle dest = {
            (GetScreenWidth() - VIRTUAL_WIDTH * scale) * 0.5f,
            (GetScreenHeight() - VIRTUAL_HEIGHT * scale) * 0.5f,
            VIRTUAL_WIDTH * scale,
            VIRTUAL_HEIGHT * scale
        };

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(worldTarget.texture, source, dest, {0, 0}, 0, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
