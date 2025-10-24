#pragma once

#include "Common.h"
#include "EventSystem.h"
#include "Enemy/IEnemy.h"

class Bullet {
public:
    Vector2 position;
    Rectangle collision;
    float speed;
    int width;
    int height;
    bool active;
    EventSystem* eventSystem;

    Bullet(float x, float y, EventSystem* es);
    void Update();
    void OnCollision(IEnemy& enemy);
    void Draw();
};
