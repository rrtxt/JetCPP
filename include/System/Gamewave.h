#pragma once

#include "Common.h"
#include "Spawner.h"
#include <memory>
#include <vector>

class Gamewave {
    public:
        Gamewave(int totalEnemies, float spawnInterval);
        void Start();
        void Update();
        void Draw();
        void Reset();
        void AddSpawner(Spawner* spawner);
        const vector<Spawner*>& GetSpawners();
        bool getIsCompleted() const { return isCompleted; }
    private:
        Spawner* spawner;
        std::vector<Spawner*> spawners;
        int totalEnemies;
        int spawnedEnemies;
        float spawnInterval;
        float spawnTimer;
        bool isCompleted;
};
