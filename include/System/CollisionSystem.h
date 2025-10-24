#pragma once

#include "Common.h"
#include "Player.h"
#include "Enemy/IEnemy.h"
#include "Bullet.h"

class CollisionSystem {
public:
    static void CheckCollisionPlayerEnemy(Player& player, vector<std::unique_ptr<IEnemy>>& enemies);
    static void CheckCollisionBulletEnemy(vector<Bullet>& bullets, vector<std::unique_ptr<IEnemy>>& enemies);
};
