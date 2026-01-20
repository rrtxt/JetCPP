#pragma once

#include "Common.h"
#include "GameState.h"
#include "IEntity.h"

class IEnemy : public IEntity {
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

        void Start() override = 0 ;
        void Update() override = 0;
        void Draw() override = 0;
        void OnCollision(IEntity& other) override = 0;
};
