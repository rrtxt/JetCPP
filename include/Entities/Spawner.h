#pragma once

#include "Common.h"
#include "EventSystem.h"
#include "Enemy.h"
#include "GameState.h"

class Spawner {
public:
    Vector2 position;
    int spawnCount = 0;
    int maxEnemies;
    std::vector<Enemy> enemies;
    EventSystem* eventSystem;
    GameState* gameState;
    float spawnRateMultiplier;
    float spawnSpread;

    Spawner(float x, float y, EventSystem* es, GameState* gs);
    void Update();
    void Spawn();
    void Draw();
    void Move(float x, float y);
};
