#include "Spawner.h"
#include "Enemy/NormalEnemy.h"
#include "Enemy/ZigZagEnemy.h"
#include "Enemy/EnemyTypes.h"
#include <memory>

Spawner::Spawner(float x, float y, EnemyType enemyType, EventSystem* es, GameState* gs) {
    position.x = x;
    position.y = y;
    eventSystem = es;
    this->enemyType = enemyType;
    gameState = gs;
    maxEnemies =  gameState->settings.GetEnemyMaxSpawnCount();
    spawnRateMultiplier = gameState->settings.GetSpawnRateMultiplier();
    spawnSpread = gameState->settings.GetEnemySpawnSpread();
}

void Spawner::Draw() {
    for(auto& enemy : enemies) {
        if(enemy) {
            enemy->Draw();
        }
    }
}

void Spawner::Spawn() {
    if (spawnCount >= maxEnemies) return;

    std::unique_ptr<IEnemy> newEnemy;
    std::cout << "Spawning enemy of type: " << static_cast<int>(enemyType) << std::endl;
    switch (enemyType) {
        case EnemyType::NORMAL:
            newEnemy = std::make_unique<NormalEnemy>(position.x + GetRandomValue(-1 * spawnSpread, spawnSpread), position.y, gameState);
            break;
        case EnemyType::ZIGZAG:
            newEnemy = std::make_unique<ZigZagEnemy>(position.x + GetRandomValue(-1 * spawnSpread, spawnSpread), position.y, gameState);
            break;
        default:
            newEnemy = std::make_unique<NormalEnemy>(position.x + GetRandomValue(-1 * spawnSpread, spawnSpread), position.y, gameState);
            break;
    }
    newEnemy->active = true;
    enemies.push_back(std::move(newEnemy));
    spawnCount++;
}

void Spawner::Update() {
    for (auto& enemy : enemies){
        if(enemy) {
            enemy->Update();
        }
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const std::unique_ptr<IEnemy>& e) { return !e || !e->active; }), enemies.end());
}

void Spawner::Move(float x, float y) {
    position.x = x;
    position.y = y;
}

void Spawner::Reset() {
    enemies.clear();
    spawnCount = 0;
}

unique_ptr<Spawner> Spawner::Clone() const {
    auto clone = make_unique<Spawner>(
        position.x,
        position.y,
        enemyType,
        eventSystem,
        gameState
    );

    clone->maxEnemies = maxEnemies;
    clone->spawnRateMultiplier = spawnRateMultiplier;
    clone->spawnSpread = spawnSpread;
    clone->spawnCount = 0;
    clone->enemies.clear();

    return clone;
}
