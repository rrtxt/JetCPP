#pragma once

#include "Common.h"
#include "External/json.hpp"
#include "GamewaveSystem.h"
#include <memory>

class Level {
public:
  string name;
  shared_ptr<GamewaveSystem> gamewave;

  Level(std::string name);
  void InitFromJSON(nlohmann::json &data, EventSystem *es, GameState *gs);
  void Update();
  void Draw();
  bool IsFinished();
};
