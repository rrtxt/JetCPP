#include "Enemy/ZigZagEnemy.h"
#include "TimeScale.h"

ZigZagEnemy::ZigZagEnemy(float x, float y, GameState* gs) : IEnemy(x, y, gs), amplitude(50.0f), frequency(3.0f), initialX(x), elapsedTime(0.0f) {
}

void ZigZagEnemy::Update() {
    if (active){
        // Move the enemy in a zigzag pattern
        elapsedTime += GetFrameTime();
        position.y += speed * speedMultiplier * GetFrameTime() * TimeScale::Get();
        position.x = initialX + amplitude * sin(frequency * elapsedTime);

        // Update collision box
        collision.x = position.x;
        collision.y = position.y;

        // Set inactive if off-screen
        if (position.y > GetScreenHeight()) {
            active = false;
        }
    }
}

void ZigZagEnemy::OnCollision() {
    if (active) {
        active = false;
    }
}

void ZigZagEnemy::Draw() {
    if (active) {
        DrawRectangle(position.x, position.y, size.x, size.y, PURPLE);
    }
}