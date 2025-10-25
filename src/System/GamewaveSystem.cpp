#include "GamewaveSystem.h"

GamewaveSystem::GamewaveSystem() : currentWaveIndex(0) {}

void GamewaveSystem::AddWave(shared_ptr<Gamewave> wave) {
    waves.push_back(wave);
}

// Starts the wave system from the first wave
void GamewaveSystem::Start() {
    currentWaveIndex = 0;
    isFinished = false;
    if (!waves.empty()) {
        waves[currentWaveIndex]->Start();
    }
}

// Resets all waves in the system
void GamewaveSystem::Reset() {
    currentWaveIndex = 0;
    isFinished = false;
    for (auto& wave : waves) {
        wave->Reset();
    }
}

// Updates the current wave and progresses to the next wave
void GamewaveSystem::Update(){
    if (currentWaveIndex >= waves.size()) return;

    auto& current = waves[currentWaveIndex];
    current->Update();

    // Check if the current wave is completed
    if(current->getIsCompleted()) {
        std::cout << "Wave " << currentWaveIndex + 1 << " completed." << std::endl;
        currentWaveIndex++;
        // Start the next wave if available
        if (currentWaveIndex < waves.size()) {
            std::cout << "Starting wave " << currentWaveIndex + 1 << std::endl;
            waves[currentWaveIndex]->Start();
        } else {
            isFinished = true;
        }
    }
}

shared_ptr<Gamewave> GamewaveSystem::GetCurrentWave() {
    if (currentWaveIndex < waves.size()) {
        return waves[currentWaveIndex];
    }
    return nullptr;
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
