#include "GamewaveSystem.h"
#include "Enemy/EnemyTypes.h"
#include "GameState.h"
#include "Gamewave.h"
#include "Spawner.h"
#include <complex>
#include <memory>

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
    currentWave->Reset();
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

    EnemyType type;
    if (waveNumber % 3 == 0){
        type = EnemyType::ZIGZAG;
    } else {
        type = EnemyType::NORMAL;
    }

    Spawner* spawner = (type == EnemyType::ZIGZAG) ? zigzagSpawner : normalSpawner;

    return make_shared<Gamewave>(spawner, enemyCount, spawnDelay);
}

void GamewaveSystem::StartNextWave(){
    currentWave = GenerateNextWave();
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
