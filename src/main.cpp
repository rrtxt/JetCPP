#include "Common.h"
#include "GameState.h"
#include "EventSystem.h"
#include "SoundSystem.h"
#include "SceneManager.h"

int main() {
    InitWindow(600, 900, "Jet Game");
    InitAudioDevice();
    
    SetTargetFPS(60);
    
    // Initialize core systems
    GameState gameState;
    EventSystem eventSystem;
    SoundSystem soundSystem;
    soundSystem.SetVolume(gameState.settings.masterVolume);
    // soundSystem.LoadSFX("shot", "assets/sound/BulletShoot.wav");   
    
    // Register game state events
    gameState.RegisterEvents(&eventSystem, &soundSystem);
    
    // Initialize scene manager
    SceneManager sceneManager(&gameState, &eventSystem, &soundSystem);
    
    std::cout << "Game initialized with Scene Manager" << std::endl;
    
    while (!WindowShouldClose()) {
        // Update current scene
        sceneManager.Update();
        
        // Render current scene
        BeginDrawing();
        sceneManager.Draw();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
