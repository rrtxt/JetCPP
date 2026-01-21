#include "GamewaveSystem.h"
#include "Enemy/EnemyTypes.h"
#include "GameState.h"
#include "Gamewave.h"
#include "Spawner.h"
#include "raylib.h"
#include <memory>

const int MAX_SPAWNER = 2;

GamewaveSystem::GamewaveSystem(GameState* state, Spawner* normal, Spawner* zigzag)
: gameState(state), currentWaveIndex(0), normalSpawner(normal), zigzagSpawner(zigzag) {}

// void GamewaveSystem::AddWave(shared_ptr<Gamewave> wave) {
//     waves.push_back(wave);
// }

// Starts the wave system from the first wave
void GamewaveSystem::Start() {
    currentWaveIndex = 0;
    isFinished = false;
    StartNextWave();
}

// Resets all waves in the system
void GamewaveSystem::Reset() {
    currentWaveIndex = 0;
    isFinished = false;
    if (currentWave){
        currentWave->Reset();
    }
}

// Updates the current wave and progresses to the next wave
void GamewaveSystem::Update(){
    if (!currentWave){
        StartNextWave();
        // currentWave = this->GenerateNextWave();
        // currentWave->Start();
        // return;
    }

    currentWave->Update();

    // Check if the current wave is completed
    if(currentWave->getIsCompleted()) {
        std::cout << "Wave " << waveNumber + 1 << " completed." << std::endl;
        StartNextWave();
    }
}

shared_ptr<Gamewave> GamewaveSystem::GetCurrentWave() {
    return currentWave;
}

shared_ptr<Gamewave> GamewaveSystem::GenerateNextWave(){
    waveNumber++;

    int enemyCount = this->gameState->settings.GetEnemyMaxSpawnCount() + waveNumber * 2;
    float spawnDelay = std::max(0.2f, baseSpawnDelay - waveNumber * 0.05f);
    return make_shared<Gamewave>(enemyCount, spawnDelay);
}

void GamewaveSystem::StartNextWave(){
    currentWave = GenerateNextWave();

    int randomNum = 0;
    for (int i = 0; i < MAX_SPAWNER; i++){
        randomNum = GetRandomValue(0, 10);
        if(randomNum > 7){
            currentWave->AddSpawner(zigzagSpawner->Clone());
        } else {
            currentWave->AddSpawner(normalSpawner->Clone());
        }
    }

    currentWave->Start();
    return;
}

// Draws the current wave
void GamewaveSystem::Draw() {
    if (currentWave) {
        currentWave->Draw();
    }
}

// Returns whether all waves have finished
bool GamewaveSystem::IsWaveFinished() {
    return isFinished;
}
