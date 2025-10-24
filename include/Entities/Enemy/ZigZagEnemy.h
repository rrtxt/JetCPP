#pragma once

#include "IEnemy.h"

class ZigZagEnemy : public IEnemy {
private:
    float amplitude;
    float frequency;
    float initialX;
    float elapsedTime;
    
public:
    ZigZagEnemy(float x, float y, GameState* gs);
    void Update() override;
    void OnCollision() override;
    void Draw() override;
};
