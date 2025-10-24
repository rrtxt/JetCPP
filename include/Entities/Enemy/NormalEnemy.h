#pragma once

#include "IEnemy.h"

class NormalEnemy : public IEnemy {
public:
    NormalEnemy(float x, float y, GameState* gs);
    void Update() override;
    void OnCollision() override;
    void Draw() override;
};
