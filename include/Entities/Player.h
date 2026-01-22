#pragma once

#include "Common.h"
#include "EventSystem.h"
#include "Bullet.h"
#include "raylib.h"
#include "IEntity.h"

class Player : public IEntity {
public:
    // Player sprite
    Image sprite;
    Texture2D texture;

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

    Player(float x , float y, EventSystem* es);
    void Start() override;
    void Update() override;
    void OnCollision(IEntity& other) override;
    void Draw() override;
};
