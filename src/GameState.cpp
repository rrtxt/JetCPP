#include "GameState.h"

void GameState::RegisterEvents(EventSystem* es) {
    es->Subscribe("OnPlayerDied", [this]() {
        this->isGameOver = true;
    });
    es->Subscribe("OnEnemyDestroyed", [this]() {
        this->score += 100;
    });
}
