#include "Common.h"
#include "TimeScale.h"
#include "EventSystem.h"
#include "GameState.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "Spawner.h"
#include "CollisionSystem.h"
#include "UISystem.h"

int main() {
    InitWindow(600, 900, "Jet Game");
    SetTargetFPS(60);
    GameState gameState;
    EventSystem eventSystem;
    Player player = Player(25, 40, GetScreenWidth() / 2, GetScreenHeight() / 2, &eventSystem);
    Spawner spawner = Spawner(GetScreenWidth() / 2 - 15, -30, &eventSystem);
    UISystem ui = UISystem(&gameState);
    gameState.RegisterEvents(&eventSystem);

    std::cout << "Initial Player Position : " << player.position.x << ", " << player.position.y << std::endl;
    
    while (!WindowShouldClose()) {
        if (!ui.isGameOver){
            // Update game state
            player.Update();
            spawner.Update();
            
            // Check collisions
            CollisionSystem::CheckCollisionPlayerEnemy(player, spawner.enemies);
            CollisionSystem::CheckCollisionBulletEnemy(player.bullets, spawner.enemies);            
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw game elements
        player.Draw();
        spawner.Draw();
        
        ui.Draw();
        EndDrawing();
    }        
    CloseWindow();
    return 0;
}
