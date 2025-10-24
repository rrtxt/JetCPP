#include "Enemy/IEnemy.h"
#include "GameState.h"

IEnemy::IEnemy(float x, float y, GameState* gs) {
    position.x = x;
    position.y = y;
    collision.x = x;
    collision.y = y;
    collision.width = 30;
    collision.height = 30;
    size.x = 30;
    size.y = 30;
    speed = 200;
    active = true;
    gameState = gs;
    speedMultiplier = gameState->settings.GetEnemySpeedMultiplier();
}