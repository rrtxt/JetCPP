#include "Common.h"
#include "EventSystem.h"
#include "GameState.h"
#include "Gamewave.h"
#include "Level.h"
#include <memory>

class LevelSystem {
private:
  vector<shared_ptr<Level>> levels;
  int currentLevelIndex = -1;
  EventSystem *eventSystem;
  GameState *gameState;

public:
  LevelSystem(EventSystem *es, GameState *gs);
  Level LoadLevelsFromJSON(string filepath);
  void StartLevel(int index);
};
