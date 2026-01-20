#pragma once

#include "IEnemy.h"
#include "IEntity.h"

class NormalEnemy : public IEnemy{
public:
    using IEnemy::IEnemy;

    NormalEnemy(float x, float y, GameState* gs);
    void Start() override;
    void Update() override;
    void OnCollision(IEntity& other) override;
    void Draw() override;
};
