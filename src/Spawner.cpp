#include "Spawner.h"
#include "TimeScale.h"

Spawner::Spawner(float x, float y, EventSystem* es) {
    position.x = x;
    position.y = y;
    spawnCooldown = 0;
    spawnRate = 0.7f; // Seconds between spawns
    maxEnemies = 5;
    eventSystem = es;
}

void Spawner::Update() {
    // Spawning cooldown
    spawnCooldown -= GetFrameTime() * TimeScale::Get();
    if (spawnCooldown < 0) spawnCooldown = 0;
    
    // Spawning
    if (spawnCooldown <= 0 && spawnCount < maxEnemies) {
        Enemy newEnemy(position.x, position.y);
        newEnemy.active = true;
        enemies.push_back(newEnemy);
        spawnCooldown = spawnRate;
        spawnCount++;
    }
    
    // Update enemies
    for (auto& enemy : enemies) {
        enemy.Update();
    }
    
    // Remove inactive enemies
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
    [](Enemy& e) { return !e.active; }), enemies.end());   

    // Update spawn position to random x
    if (spawnCount >= maxEnemies && enemies.empty()) {
        Move(GetRandomValue(0, GetScreenWidth() - 30), position.y);
        spawnCount = 0;
    }
}

void Spawner::Draw() {
    for(auto& enemy : enemies) {
        enemy.Draw();
    }
}

void Spawner::Move(float x, float y) {
    position.x = x;
    position.y = y;
}
