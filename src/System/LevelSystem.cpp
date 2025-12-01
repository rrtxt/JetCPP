#include "LevelSystem.h"
#include "EventSystem.h"
#include "External/json.hpp"
#include "GameState.h"
#include "Level.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

LevelSystem::LevelSystem(EventSystem *es, GameState *gs) {
  gameState = gs;
  eventSystem = es;
}

// Load level from json file
Level LevelSystem::LoadLevelsFromJSON(string filepath) {
  ifstream file(filepath);
  nlohmann::json j;
  file >> j;

  shared_ptr<Level> level = make_shared<Level>(j["levelName"]);
  level->InitFromJSON(j, this->eventSystem, this->gameState);
  return *level;
}

// Start a level based on index
void LevelSystem::StartLevel(int index) {
  string filepath = "assets/levels/level_" + to_string(index) + ".json";
  ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "[LEVELSYSTEM] Error while reading " << filepath << endl;
    return;
  }

  Level level = LoadLevelsFromJSON(filepath);

  // Go to in game scene with loaded level data
}
