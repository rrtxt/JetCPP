#pragma once

#include "Common.h"
#include "GameState.h"
#include "Gamewave.h"
#include <memory>

class GamewaveSystem{
    private:
        std::vector<shared_ptr<Gamewave>> waves;
        GameState* gameState;
        int currentWaveIndex;
        bool isFinished = false;

        Spawner* normalSpawner = nullptr;
        Spawner* zigzagSpawner = nullptr;
    public:
        int waveNumber = 0;
        int baseSpawnDelay = 1.0f;

        GamewaveSystem(GameState* gameState, Spawner* normalSpawner, Spawner* zigzagSpawner);
        void AddWave(shared_ptr<Gamewave> wave);
        void Start();
        void Update();
        void Reset();
        shared_ptr<Gamewave> GetCurrentWave();
        shared_ptr<Gamewave> GenerateNextWave();
        void StartNextWave();
        void Draw();
        bool IsWaveFinished();
};
