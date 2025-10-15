#include "Spawner.h"
#include "TimeScale.h"

Spawner::Spawner(float x, float y, EventSystem* es, GameState* gs) {
    position.x = x;
    position.y = y;
    eventSystem = es;   
    gameState = gs;
    maxEnemies =  gameState->settings.GetEnemyMaxSpawnCount();
    spawnRateMultiplier = gameState->settings.GetSpawnRateMultiplier();
    spawnSpread = gameState->settings.GetEnemySpawnSpread();
}

void Spawner::Draw() {
    for(auto& enemy : enemies) {
        enemy.Draw();
    }
}

void Spawner::Spawn() {
    Enemy newEnemy(position.x + GetRandomValue(-1 * spawnSpread, spawnSpread), position.y, gameState);
    newEnemy.active = true;
    enemies.push_back(newEnemy);
    spawnCount++;
}

void Spawner::Update() {
    for (auto& enemy : enemies){
        enemy.Update();
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& e) { return !e.active; }), enemies.end());
}

void Spawner::Move(float x, float y) {
    position.x = x;
    position.y = y;
}
