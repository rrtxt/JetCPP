#include "Enemy/NormalEnemy.h"
#include "Common.h"
#include "IEntity.h"
#include "TimeScale.h"
#include "raylib.h"

NormalEnemy::NormalEnemy(float x, float y, GameState* gs) : IEnemy(x, y, gs) {
    speedMultiplier = gameState->settings.GetEnemySpeedMultiplier();
}

void NormalEnemy::Start(){
    sprite = LoadImage("assets/image/enemies_blue.png");
    texture = LoadTextureFromImage(sprite);
    UnloadImage(sprite);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
}

void NormalEnemy::Update() {
    if(active) {
        // Multiply speed by enemy speed multiplier from game settings
        position.y += speed * speedMultiplier * GetFrameTime() * TimeScale::Get();

        // Update collision box
        collision.y = position.y;

        // Set inactive if off-screen
        if(position.y > VIRTUAL_HEIGHT) {
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
