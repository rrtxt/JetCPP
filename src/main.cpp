#include "raylib.h"
#include "raymath.h"
#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

const int VELOCITY = 200;
const int TIMESCALE = 1;
class Bullet{
    public:
        Vector2 position;
        Rectangle collision;
        float speed;
        int width;
        int height;
        bool active;
        Bullet(float x, float y){
            position.x = x;
            position.y = y;
            collision.x = x;
            collision.y = y;
            width = 5;
            height = 10;
            collision.width = width;
            collision.height = height;
            speed = 350;
        }
        void Update(){
            if(active){
                // Move upward
                position.y -= speed * GetFrameTime();
                
                // Update collision box
                collision.y = position.y;
                
                // Set inactive if off-screen
                if(position.y + height < 0){
                    active = false;
                }
            }
        }

        void Draw(){
            if(active){
                DrawRectangle(position.x, position.y, width, height, BLACK);
            }
        }
};

class Player{
    public:
        Vector2 position;
        Vector2 size;
        Vector2 inputDirection;
        Rectangle collision;
        std::vector<Bullet> bullets;
        float shootCooldown;
        float fireRate;
        Player(int width, int height, float x , float y){
            position.x = x;
            position.y = y;
            collision.x = x;
            collision.y = y;
            collision.width = width;
            collision.height = height;
            size.x = width;
            size.y = height;
            shootCooldown = 0;
            fireRate = 0.2f; // Seconds between shots
        }

        void Update(){
            // Movement
            inputDirection = {0, 0};
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
                inputDirection.y -= 1;
            }
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
                inputDirection.y += 1;
            }
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                inputDirection.x += 1;
            }
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                inputDirection.x -= 1;
            }

            // Normalize diagonal movement
            if (Vector2Length(inputDirection) > 0){
                inputDirection = Vector2Normalize(inputDirection);
            }

            // Shooting cooldown
            shootCooldown -= GetFrameTime();
            if (shootCooldown < 0) shootCooldown = 0;
            
            // Shooting
            if (IsKeyDown(KEY_SPACE) && shootCooldown <= 0) {
                Bullet newBullet(position.x + size.x / 2 - 2.5f, position.y);
                newBullet.active = true;
                bullets.push_back(newBullet);
                shootCooldown = fireRate;
            }

            // Update bullets
            for (auto& bullet : bullets) {
                bullet.Update();
            }

            // Remove inactive bullets
            bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                [](Bullet& b) { return !b.active; }), bullets.end());

            // Update position
            Vector2 velocity = Vector2Scale(inputDirection, VELOCITY * GetFrameTime() * TIMESCALE);
            position = Vector2Add(position, velocity);
            position = Vector2Clamp(position, {0, 0}, {GetScreenWidth() - size.x, GetScreenHeight() - size.y});

            // Update collision box
            collision.x = position.x;
            collision.y = position.y;
        }

        void Draw(){
            DrawRectangle(position.x, position.y, size.x, size.y, RED);
            for(auto& bullet : bullets){
                bullet.Draw();
            }
        }
};



class Enemy{
    public:
    Vector2 position;
    Vector2 size;
    Rectangle collision;
    float speed;
    bool active;
    Enemy(float x, float y){
            position.x = x;
            position.y = y;
            collision.x = x;
            collision.y = y;
            collision.width = 30;
            collision.height = 30;
            size.x = 30;
            size.y = 30;
            speed = 100;
            active = true;
        }
        void Update(){
            if(active){
                // Move downward
                position.y += speed * GetFrameTime();

                // Update collision box
                collision.y = position.y;
                
                // Set inactive if off-screen
                if(position.y > GetScreenHeight()){
                    active = false;
                }
            }
        }

        void Draw(){
            if(active){
                DrawRectangle(position.x, position.y, size.x, size.y, BLUE);
            }
        }
};
    
    class Spawner{
        public:
        Vector2 position;
        float spawnCooldown;
        float spawnRate;
        int maxEnemies;
        std::vector<Enemy> enemies;
        Spawner(float x, float y){
            position.x = x;
            position.y = y;
            spawnCooldown = 0;
            spawnRate = 1.0f; // Seconds between spawns
            maxEnemies = 5;
        }
        void Update(){
            // Spawning cooldown
            spawnCooldown -= GetFrameTime();
            if (spawnCooldown < 0) spawnCooldown = 0;
            
            // Spawning
            if (spawnCooldown <= 0 && enemies.size() < maxEnemies) {
                Enemy newEnemy(position.x, position.y);
                newEnemy.active = true;
                enemies.push_back(newEnemy);
                spawnCooldown = spawnRate;
            }
            
            // Update enemies
            for (auto& enemy : enemies) {
                enemy.Update();
            }
            
            // Remove inactive enemies
            enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](Enemy& e) { return !e.active; }), enemies.end());   
        }
        void Draw(){
            for(auto& enemy : enemies){
                enemy.Draw();
            }
        }
    };

    class CollisionSystem{
        public:
            static void CheckCollisionPlayerEnemy(Player& player, vector<Enemy>& enemies){
                for(auto& enemy : enemies){
                    if(enemy.active && CheckCollisionRecs(player.collision, enemy.collision)){
                        enemy.active = false;
                        std::cout << "Collision Detected!" << std::endl;
                    }
                }
            }

            static void CheckCollisionBulletEnemy(vector<Bullet>& bullets, vector<Enemy>& enemies){
                for(auto& bullet : bullets){
                    for(auto& enemy : enemies){
                        if(bullet.active && enemy.active && CheckCollisionRecs(bullet.collision, enemy.collision)){
                            bullet.active = false;
                            enemy.active = false;
                            std::cout << "Bullet hit Enemy!" << std::endl;
                        }
                    }
                }
            }
    };
    
    int main() {
        InitWindow(600, 900, "Jet Game");
        SetTargetFPS(60);
        Player player = Player(25, 40, GetScreenWidth() / 2, GetScreenHeight() / 2);
        Spawner spawner = Spawner(GetScreenWidth() / 2 - 15, -30);
        std::cout << "Initial Player Position : " << player.position.x << ", " << player.position.y << std::endl;
        
        while (!WindowShouldClose()) {
            // Update game state
            player.Update();
            spawner.Update();

            // Check collisions
            CollisionSystem::CheckCollisionPlayerEnemy(player, spawner.enemies);
            CollisionSystem::CheckCollisionBulletEnemy(player.bullets, spawner.enemies);
            
            BeginDrawing();
            ClearBackground(RAYWHITE);

            // Draw game elements
            player.Draw();
            spawner.Draw();  
            EndDrawing();
        }
        
        CloseWindow();
        return 0;                                                                                                                                                              
    }
    
    
    
    
