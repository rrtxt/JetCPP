#pragma once

#include "Common.h"
#include "EventSystem.h"
#include "Enemy/IEnemy.h"
#include "Enemy/EnemyTypes.h"
#include "GameState.h"

class Spawner {
public:
    Vector2 position;
    int spawnCount = 0;
    int maxEnemies;
    std::vector<std::unique_ptr<IEnemy>> enemies;
    EventSystem* eventSystem;
    GameState* gameState;
    float spawnRateMultiplier;
    float spawnSpread;
    EnemyType enemyType;
    
    Spawner(float x, float y, EnemyType enemyType, EventSystem* es, GameState* gs);
    void Update();
    void Spawn();
    void Draw();
    void Reset();
    void Move(float x, float y);
};
