#pragma once

#include "Common.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class CollisionSystem {
public:
    static void CheckCollisionPlayerEnemy(Player& player, vector<Enemy>& enemies);
    static void CheckCollisionBulletEnemy(vector<Bullet>& bullets, vector<Enemy>& enemies);
};
