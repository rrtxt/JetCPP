#include "CollisionSystem.h"

void CollisionSystem::CheckCollisionPlayerEnemy(Player& player, vector<Enemy>& enemies) {
    for(auto& enemy : enemies) {
        if(CheckCollisionRecs(player.collision, enemy.collision)) {
            player.OnCollision();
            enemy.OnCollision();
            std::cout << "Collision Detected!" << std::endl;
        }
    }
}

void CollisionSystem::CheckCollisionBulletEnemy(vector<Bullet>& bullets, vector<Enemy>& enemies) {
    for(auto& bullet : bullets) {
        for(auto& enemy : enemies) {
            if(CheckCollisionRecs(bullet.collision, enemy.collision)) {
                bullet.OnCollision(enemy);
                enemy.OnCollision();
                std::cout << "Bullet hit Enemy!" << std::endl;
            }
        }
    }
}
