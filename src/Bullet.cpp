#include "Bullet.h"
#include "TimeScale.h"

Bullet::Bullet(float x, float y, EventSystem* es) {
    position.x = x;
    position.y = y;
    collision.x = x;
    collision.y = y;
    width = 5;
    height = 10;
    collision.width = width;
    collision.height = height;
    speed = 350;
    eventSystem = es;
}

void Bullet::Update() {
    if(active) {
        // Move upward
        position.y -= speed * GetFrameTime() * TimeScale::Get();
        
        // Update collision box
        collision.y = position.y;
        
        // Set inactive if off-screen
        if(position.y + height < 0) {
            active = false;
        }
    }
}

void Bullet::OnCollision(Enemy& enemy) {
    if (active && enemy.active) {
        active = false; 

        if(eventSystem) {
            eventSystem->Emit("OnEnemyDestroyed");
        }
    }
}

void Bullet::Draw() {
    if(active) {
        DrawRectangle(position.x, position.y, width, height, BLACK);
    }
}
