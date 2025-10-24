#pragma once

#include "Common.h"
#include "Spawner.h"

class Gamewave {
    public:
        Gamewave(Spawner* spawner, int totalEnemies, float spawnInterval);
        void Start();
        void Update();
        void Draw();
        void Reset();
        bool getIsCompleted() const { return isCompleted; }
    private:
        Spawner* spawner;
        int totalEnemies;
        int spawnedEnemies;
        float spawnInterval;
        float spawnTimer; 
        bool isCompleted;
};