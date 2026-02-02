#include "Player.h"
#include "Common.h"
#include "IEntity.h"
#include "TimeScale.h"
#include "raylib.h"
#include <cstdio>

Player::Player(float x , float y, EventSystem* es) : IEntity() {
    position.x = x;
    position.y = y;
    collision.x = x;
    collision.y = y;
    collision.width = PLAYER_WIDTH;
    collision.height = PLAYER_HEIGHT;
    size.x = PLAYER_WIDTH;
    size.y = PLAYER_HEIGHT;
    shootCooldown = 0;
    fireRate = 0.2f; // Seconds between shots
    maxHealth = 3;
    currentHealth = maxHealth;
    eventSystem = es;
}

void Player::Start(){
    printf("Load player texture...");
    // load character texture
    sprite = LoadImage("assets/image/jet.png");
    texture = LoadTextureFromImage(sprite);
    UnloadImage(sprite);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
}

void Player::Update() {
    // Movement
    inputDirection = {0, 0};
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        inputDirection.y = -1;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        inputDirection.y = 1;
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        inputDirection.x = 1;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        inputDirection.x = -1;
    }

    // Normalize diagonal movement
    if (Vector2Length(inputDirection) > 0) {
        inputDirection = Vector2Normalize(inputDirection);
    }

    // Shooting cooldown
    shootCooldown -= GetFrameTime() * TimeScale::Get();
    if (shootCooldown < 0) shootCooldown = 0;

    // Shooting
    if (IsKeyDown(KEY_SPACE) && shootCooldown <= 0) {
        Bullet newBullet(position.x + size.x / 2 - 2.5f, position.y, eventSystem);
        eventSystem->Emit("OnBulletSpawn");
        newBullet.active = true;
        bullets.push_back(newBullet);
        shootCooldown = fireRate;
    }

    // Update bullets
    for (auto& bullet : bullets) {
        bullet.Update();
    }

    // Remove inactive bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](Bullet& b) { return !b.active; }), bullets.end());

    // Update position
    Vector2 velocity = Vector2Scale(inputDirection, VELOCITY * GetFrameTime() * TimeScale::Get());
    position = Vector2Add(position, velocity);
    position = Vector2Clamp(position, {0, 0}, {VIRTUAL_WIDTH - size.x, VIRTUAL_HEIGHT - size.y});

    // Update collision box
    collision.x = position.x;
    collision.y = position.y;
}

void Player::OnCollision(IEntity& other) {
    if (currentHealth > 1) {
        eventSystem->Emit("OnPlayerHit");
    } else {
        if(eventSystem) {
            eventSystem->Emit("OnPlayerDied");
        }
        TimeScale::Set(0);
    }
}

void Player::Draw() {
    // DrawRectangleLines(position.x, position.y, size.x, size.y, RED);
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

    for(auto& bullet : bullets) {
        bullet.Draw();
    }
}
