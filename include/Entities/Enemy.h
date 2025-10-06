#pragma once

#include "Common.h"
#include "GameState.h"

class Enemy {
public:
    Vector2 position;
    Vector2 size;
    Rectangle collision;
    float speed;
    bool active;
    GameState* gameState;
    float speedMultiplier;

    Enemy(float x, float y, GameState* gs);
    void Update();
    void OnCollision();
    void Draw();
};
