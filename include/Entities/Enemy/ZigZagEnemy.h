#pragma once

#include "IEnemy.h"
#include "IEntity.h"

class ZigZagEnemy : public IEnemy {
private:
    float amplitude;
    float frequency;
    float initialX;
    float elapsedTime;

public:
    using IEnemy::IEnemy;

    ZigZagEnemy(float x, float y, GameState* gs);
    void Start() override;
    void Update() override;
    void OnCollision(IEntity& other) override;
    void Draw() override;
};
