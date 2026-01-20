#pragma once

#include "Common.h"
#include "EventSystem.h"
#include "Bullet.h"
#include "raylib.h"

class Player {
public:
    // Player sprite
    Image sprite;
    Texture2D characterTexture;

    // Coordinates and size
    Vector2 position;
    Vector2 size;
    Vector2 inputDirection;
    Rectangle collision;

    // Player status
    int maxHealth;
    int currentHealth;

    // Shooting
    std::vector<Bullet> bullets;
    float shootCooldown;
    float fireRate;

    // Events
    EventSystem* eventSystem;

    Player(int width, int height, float x , float y, EventSystem* es);
    void Update();
    void OnCollision();
    void Draw();
};
