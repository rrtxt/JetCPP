#include "Gamewave.h"

Gamewave::Gamewave(Spawner* spawner, int totalEnemies, float spawnInterval)
    : spawner(spawner), totalEnemies(totalEnemies), spawnInterval(spawnInterval),
      spawnedEnemies(0), spawnTimer(0.0f), isCompleted(false) {}

void Gamewave::Start() {
    spawnedEnemies = 0;
    spawnTimer = 0.0f;
    isCompleted = false;
    spawner->Move(GetRandomValue(50, GetScreenWidth() - 50), -30);
}

void Gamewave::Update() {
    if (isCompleted) return;

    spawnTimer += GetFrameTime();
    if (spawnedEnemies < totalEnemies && spawnTimer >= spawnInterval) {
        spawner->Spawn();
        spawnedEnemies++;
        spawnTimer = 0.0f;
    }

    spawner->Update();

    if (spawnedEnemies >= totalEnemies && spawner->enemies.empty()) {
        isCompleted = true;
    }
}

void Gamewave::Draw() {
    spawner->Draw();
}