#include "CollisionSystem.h"

void CollisionSystem::CheckCollisionPlayerEnemy(Player& player, vector<std::unique_ptr<IEnemy>>& enemies) {
    for(auto& enemy : enemies) {
        if(enemy && CheckCollisionRecs(player.collision, enemy->collision)) {
            player.OnCollision(*enemy);
            enemy->OnCollision(player);
            std::cout << "Collision Detected!" << std::endl;
        }
    }
}

void CollisionSystem::CheckCollisionBulletEnemy(vector<Bullet>& bullets, vector<std::unique_ptr<IEnemy>>& enemies) {
    for(auto& bullet : bullets) {
        for(auto& enemy : enemies) {
            if(enemy && CheckCollisionRecs(bullet.collision, enemy->collision)) {
                bullet.OnCollision(*enemy);
                enemy->OnCollision(bullet);
                std::cout << "Bullet hit Enemy!" << std::endl;
            }
        }
    }
}
