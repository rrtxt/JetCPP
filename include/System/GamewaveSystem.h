#pragma once

#include "Common.h"
#include "Gamewave.h"
#include <memory>

class GamewaveSystem{
    private:
        std::vector<shared_ptr<Gamewave>> waves;
        int currentWaveIndex;
        bool isFinished = false;
    public:
        GamewaveSystem();
        void AddWave(shared_ptr<Gamewave> wave);
        void Start();
        void Update();
        void Reset();
        shared_ptr<Gamewave> GetCurrentWave();
        void Draw();
        bool IsWaveFinished();
};