#include "Enemy.h"
#include "TimeScale.h"

Enemy::Enemy(float x, float y) {
    position.x = x;
    position.y = y;
    collision.x = x;
    collision.y = y;
    collision.width = 30;
    collision.height = 30;
    size.x = 30;
    size.y = 30;
    speed = 200;
    active = true;
}

void Enemy::Update() {
    if(active) {
        // Move downward
        position.y += speed * GetFrameTime() * TimeScale::Get();

        // Update collision box
        collision.y = position.y;
        
        // Set inactive if off-screen
        if(position.y > GetScreenHeight()) {
            active = false;
        }
    }
}

void Enemy::OnCollision() {
    if (active) {
        active = false;
    }
}

void Enemy::Draw() {
    if(active) {
        DrawRectangle(position.x, position.y, size.x, size.y, BLUE);
    }
}
