#include "Enemy/IEnemy.h"
#include "GameState.h"

IEnemy::IEnemy(float x, float y, GameState* gs) {
    position.x = x;
    position.y = y;
    collision.x = x;
    collision.y = y;
    collision.width = ENEMY_WIDTH;
    collision.height = ENEMY_HEIGHT;
    size.x = ENEMY_WIDTH;
    size.y = ENEMY_HEIGHT;
    speed = ENEMY_SPEED;
    active = true;
    gameState = gs;
    speedMultiplier = gameState->settings.GetEnemySpeedMultiplier();
}
