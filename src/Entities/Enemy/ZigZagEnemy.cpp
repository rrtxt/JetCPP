#include "Enemy/ZigZagEnemy.h"
#include "IEntity.h"
#include "TimeScale.h"
#include <raylib.h>

ZigZagEnemy::ZigZagEnemy(float x, float y, GameState* gs) : IEnemy(x, y, gs), amplitude(50.0f), frequency(3.0f), initialX(x), elapsedTime(0.0f) {
}

void ZigZagEnemy::Start(){
    sprite = LoadImage("assets/image/enemies_red.png");
    texture = LoadTextureFromImage(sprite);
    UnloadImage(sprite);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
}

void ZigZagEnemy::Update() {
    if (active){
        // Move the enemy in a zigzag pattern
        elapsedTime += GetFrameTime() * TimeScale::Get();
        position.y += speed * speedMultiplier * GetFrameTime() * TimeScale::Get();
        position.x = initialX + amplitude * sin(frequency * elapsedTime) * TimeScale::Get();

        // Update collision box
        collision.x = position.x;
        collision.y = position.y;

        // Set inactive if off-screen
        if (position.y > VIRTUAL_HEIGHT) {
            active = false;
        }
    }
}

void ZigZagEnemy::OnCollision(IEntity& other) {
    if (active) {
        active = false;
    }
}

void ZigZagEnemy::Draw() {
    if (active) {
        // DrawRectangleLines(position.x, position.y, size.x, size.y, BLUE);
        // DrawTexture(characterTexture, position.x, position.y, WHITE);
        Rectangle source = {
            0, 0,
            (float)texture.width,
            (float)texture.height
        };

        Rectangle dest = {
            position.x + size.x / 2.0f,
            position.y + size.y / 2.0f,
            texture.width * SPRITE_SCALE,
            texture.height * SPRITE_SCALE
        };

        Vector2 origin = {
            dest.width / 2,
            dest.height / 2
        };
        DrawTexturePro(
                    texture,
                    source,
                    dest,
                    origin,
                    0.0f,
                    WHITE
        );
    }
}
