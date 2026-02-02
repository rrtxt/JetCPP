#include "Gamewave.h"
#include "Common.h"
#include "Spawner.h"
#include "TimeScale.h"
#include "raylib.h"
#include "raymath.h"
#include <algorithm>
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

    int screenW = VIRTUAL_WIDTH;
    int x1 = 0;
    int x2 = 0;

    // Pick first spawner freely
    x1 = GetRandomValue(MARGIN, screenW - MARGIN);

    // Pick second spawner until distance is OK
    if (x1 <= screenW / 2) {
        int minX = x1 + MIN_DISTANCE;
        int maxX = screenW - MARGIN;
        x2 = (minX <= maxX) ? GetRandomValue(minX, maxX) : maxX;
    } else {
        int minX = MARGIN;
        int maxX = x1 - MIN_DISTANCE;
        x2 = (minX <= maxX) ? GetRandomValue(minX, maxX) : minX;
    }

    printf("Move spawner 1 to %d, %d\n", x1, SPAWN_Y);
    spawners[0]->Move(x1, SPAWN_Y);

    printf("Move spawner 2 to %d, %d\n", x2, SPAWN_Y);
    spawners[1]->Move(x2, SPAWN_Y);
    printf("Finish moving spawner\n");
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
