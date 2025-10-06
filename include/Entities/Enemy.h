#pragma once

#include "Common.h"

class Enemy {
public:
    Vector2 position;
    Vector2 size;
    Rectangle collision;
    float speed;
    bool active;

    Enemy(float x, float y);
    void Update();
    void OnCollision();
    void Draw();
};
