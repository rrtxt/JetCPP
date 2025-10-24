#pragma once

#include "Common.h"
#include "GameState.h"

class IEnemy {
    public:
        Vector2 position;
        Vector2 size;
        Rectangle collision;
        float speed;
        bool active;
        GameState* gameState;
        float speedMultiplier;

        IEnemy(float x, float y, GameState* gs);
        virtual ~IEnemy() = default;
        
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual void OnCollision() = 0;
};