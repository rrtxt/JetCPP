#include "GamewaveSystem.h"

GamewaveSystem::GamewaveSystem() : currentWaveIndex(0) {}

void GamewaveSystem::AddWave(shared_ptr<Gamewave> wave) {
    waves.push_back(wave);
}

// Starts the wave system from the first wave
void GamewaveSystem::Start() {
    currentWaveIndex = 0;
    if (!waves.empty()) {
        waves[currentWaveIndex]->Start();
    }
}

// Updates the current wave and progresses to the next wave
void GamewaveSystem::Update(){
    if (currentWaveIndex >= waves.size()) return;

    auto& current = waves[currentWaveIndex];
    current->Update();

    // Check if the current wave is completed
    if(current->getIsCompleted()) {
        currentWaveIndex++;
        // Start the next wave if available
        if (currentWaveIndex < waves.size()) {
            waves[currentWaveIndex]->Start();
        } else {
            isFinished = true;
        }
    }
}

// Draws the current wave
void GamewaveSystem::Draw() {
    if (currentWaveIndex < waves.size()) {
        waves[currentWaveIndex]->Draw();
    }
}

// Returns whether all waves have finished
bool GamewaveSystem::IsWaveFinished() {
    return isFinished;
}
