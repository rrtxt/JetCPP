#include "Gamewave.h"
#include "Spawner.h"
#include "TimeScale.h"
#include "raylib.h"
#include <cstdio>
#include <utility>
#include <memory>

const int SPAWN_Y = -30;
const int MIN_DISTANCE = 400;
const int MARGIN = 50;

Gamewave::Gamewave(int totalEnemies, float spawnInterval)
    : totalEnemies(totalEnemies), spawnInterval(spawnInterval),
      spawnedEnemies(0), spawnTimer(0.0f), isCompleted(false) {}

void Gamewave::Start() {
    spawnedEnemies = 0;
    spawnTimer = 0.0f;
    isCompleted = false;
    // spawner->Move(GetRandomValue(50, GetScreenWidth() - 50), -30);
    if (spawners.empty()) return;

    int screenW = GetScreenWidth();
    int x1 = 0;
    int x2 = 0;

    // Pick first spawner freely
    x1 = GetRandomValue(MARGIN, screenW - MARGIN);

    // Pick second spawner until distance is OK
    do {
        x2 = GetRandomValue(MARGIN, screenW - MARGIN);
    } while (std::abs(x1 - x2) < MIN_DISTANCE);

    printf("Move spawner 1 to %d, %d\n", x1, SPAWN_Y);
    printf("Move spawner 2 to %d, %d\n", x2, SPAWN_Y);
    spawners[0]->Move(x1, SPAWN_Y);
    spawners[1]->Move(x2, SPAWN_Y);
}

void Gamewave::Update() {
    if (isCompleted) return;

    spawnTimer += GetFrameTime() * TimeScale::Get();
    if (spawnedEnemies < totalEnemies && spawnTimer >= spawnInterval) {
        for (auto& spawner : spawners){
            if (spawnedEnemies >= totalEnemies) break;

            spawner->Spawn();
            spawnedEnemies++;
        }

        spawnTimer = 0.0f;
    }

    for (auto& spawner : spawners){
        spawner->Update();
    }

    bool isAllEmpty = true;
    for (const auto& spawner : spawners) {
        if (!spawner->enemies.empty()) {
            isAllEmpty = false;
            break;
        }
    }

    if (spawnedEnemies >= totalEnemies && isAllEmpty) {
        isCompleted = true;
    }
}

void Gamewave::Reset() {
    spawnedEnemies = 0;
    spawnTimer = 0.0f;
    isCompleted = false;
    for (auto& spawner : spawners){
        spawner->Reset();
    }
}

void Gamewave::AddSpawner(unique_ptr<Spawner> spawner){
    spawners.push_back(std::move(spawner));
}

const vector<unique_ptr<Spawner>>& Gamewave::GetSpawners() const{
    return spawners;
}

void Gamewave::Draw() {
    for (auto& spawner : spawners){
        spawner->Draw();
    }
}
