#pragma once

#include "Common.h"
#include "EventSystem.h"
#include "Enemy/IEnemy.h"
#include "IEntity.h"

class Bullet : public IEntity{
public:
    Vector2 position;
    Rectangle collision;
    float speed;
    int width;
    int height;
    bool active;
    EventSystem* eventSystem;

    Bullet(float x, float y, EventSystem* es);
    void Start() override;
    void Update() override;
    void OnCollision(IEntity& other) override;
    void Draw() override;
};
