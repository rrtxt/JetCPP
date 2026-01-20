#include "Enemy/NormalEnemy.h"
#include "IEntity.h"
#include "TimeScale.h"

NormalEnemy::NormalEnemy(float x, float y, GameState* gs) : IEnemy(x, y, gs) {
    speedMultiplier = gameState->settings.GetEnemySpeedMultiplier();
}

void NormalEnemy::Start(){}

void NormalEnemy::Update() {
    if(active) {
        // Multiply speed by enemy speed multiplier from game settings
        position.y += speed * speedMultiplier * GetFrameTime() * TimeScale::Get();

        // Update collision box
        collision.y = position.y;

        // Set inactive if off-screen
        if(position.y > GetScreenHeight()) {
            active = false;
        }
    }
}

void NormalEnemy::OnCollision(IEntity& other) {
    if (active) {
        active = false;
    }
}

void NormalEnemy::Draw() {
    if(active) {
        DrawRectangle(position.x, position.y, size.x, size.y, BLUE);
    }
}
