#include "System/Level.h"
#include "Enemy/EnemyTypes.h"
#include "EventSystem.h"
#include "External/json.hpp"
#include "GameState.h"
#include "Gamewave.h"
#include "GamewaveSystem.h"
#include "Spawner.h"
#include <memory>
#include <raylib.h>
#include <string>

Level::Level(std::string name) { this->name = name; }

void Level::InitFromJSON(nlohmann::json &data, EventSystem *es, GameState *gs) {
  auto waveSystem = std::shared_ptr<GamewaveSystem>();

  for (auto &waveData : data["waves"]) {
    EnemyType enemyType;
    int maxEnemies = waveData["maxEnemies"];
    float spawnInterval = waveData["spawnInterval"];
    float spread = waveData["spread"];
    if (waveData["enemyType"] == "normal") {
      enemyType = EnemyType::NORMAL;
    } else if (waveData["enemyType"] == "zigzag") {
      enemyType = EnemyType::ZIGZAG;
    } else {
      enemyType = EnemyType::NORMAL;
    }

    unique_ptr<Spawner> spawner =
        make_unique<Spawner>(GetScreenWidth() / 2 - 15, -30, enemyType, es, gs);

    spawner->spawnSpread = spread;

    // auto wave = make_shared<Gamewave>(spawner.get(), maxEnemies, spawnInterval);

    // waveSystem->AddWave(wave);
  }
}
