#include "Common.h"
#include "GameState.h"
#include "EventSystem.h"
#include "SceneManager.h"

int main() {
    InitWindow(600, 900, "Jet Game");
    SetTargetFPS(60);
    
    // Initialize core systems
    GameState gameState;
    EventSystem eventSystem;
    
    // Register game state events
    gameState.RegisterEvents(&eventSystem);
    
    // Initialize scene manager
    SceneManager sceneManager(&gameState, &eventSystem);
    
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
