#include "raylib.h"
#include "raymath.h"
#include "iostream"
#include "vector"
#include "algorithm"
#include "functional"

using namespace std;

const int VELOCITY = 200;
bool isGameOver = false;
class TimeScale {
    private:
        static int timescale;
    public:
        TimeScale(int initial = 1) { timescale = initial; }
        static int Get() { return timescale; }
        static void Set(int value) { 
            if(value < 0) value = 0;
            timescale = value;
        }
};

int TimeScale::timescale = 1;

class EventSystem{
    public:
    using Callback = std::function<void()>;
    
    void Subscribe(const std::string& eventName, Callback callback) {
        listeners[eventName].push_back(callback);
    }
    
    void Emit(const std::string& eventName) {
        if (listeners.find(eventName) != listeners.end()) {
            for (const auto& callback : listeners[eventName]) {
                callback();
            }
        }
    }

    private:
        std::unordered_map<std::string, std::vector<Callback>> listeners;
};

class GameState{
    public:
        bool isGameOver;
        int score = 0;

        void RegisterEvents(EventSystem* es){
            es->Subscribe("OnPlayerDied", [this]() {
                this->isGameOver = true;
            });
            es->Subscribe("OnEnemyDestroyed", [this]() {
                this->score += 100;
            });
        }

};

TimeScale TIMESCALE(1);
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
                position.y -= speed * GetFrameTime() * TimeScale::Get();
                
                // Update collision box
                collision.y = position.y;
                
                // Set inactive if off-screen
                if(position.y + height < 0){
                    active = false;
                }
            }
        }

        void OnCollision(){
            if (active){
                active = false;
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
        // Coordinates and size
        Vector2 position;
        Vector2 size;
        Vector2 inputDirection;
        Rectangle collision;

        // Player status
        int maxHealth;
        int currentHealth;

        // Shooting
        std::vector<Bullet> bullets;
        float shootCooldown;
        float fireRate;

        // Events
        EventSystem* eventSystem;

        Player(int width, int height, float x , float y, EventSystem* es){
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
            maxHealth = 3;
            currentHealth = maxHealth;

            eventSystem = es;
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
            shootCooldown -= GetFrameTime() * TimeScale::Get();
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
            Vector2 velocity = Vector2Scale(inputDirection, VELOCITY * GetFrameTime() * TimeScale::Get());
            position = Vector2Add(position, velocity);
            position = Vector2Clamp(position, {0, 0}, {GetScreenWidth() - size.x, GetScreenHeight() - size.y});

            // Update collision box
            collision.x = position.x;
            collision.y = position.y;
        }

        void OnCollision(){
            if (currentHealth > 0){
                currentHealth--;
                std::cout << "Player Health: " << currentHealth << std::endl;
            } else {
                if(eventSystem){
                    eventSystem->Emit("OnPlayerDied");
                }
                TimeScale::Set(0);
                std::cout << "Player Defeated!" << std::endl;
            }
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
    EventSystem* eventSystem;
    Enemy(float x, float y, EventSystem* es){
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
            eventSystem = es;
        }
        void Update(){
            if(active){
                // Move downward
                position.y += speed * GetFrameTime() * TimeScale::Get();

                // Update collision box
                collision.y = position.y;
                
                // Set inactive if off-screen
                if(position.y > GetScreenHeight()){
                    active = false;
                }
            }
        }

        void OnCollision(){
            if (active){
                eventSystem->Emit("OnEnemyDestroyed");
                active = false;
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
        int spawnCount = 0;
        int maxEnemies;
        std::vector<Enemy> enemies;
        EventSystem* eventSystem;
        Spawner(float x, float y, EventSystem* es){
            position.x = x;
            position.y = y;
            spawnCooldown = 0;
            spawnRate = 0.7f; // Seconds between spawns
            maxEnemies = 5;
            eventSystem = es;
        }
        void Update(){
            // Spawning cooldown
            spawnCooldown -= GetFrameTime() * TimeScale::Get();
            if (spawnCooldown < 0) spawnCooldown = 0;
            
            // Spawning
            if (spawnCooldown <= 0 && spawnCount < maxEnemies) {
                Enemy newEnemy(position.x, position.y, eventSystem);
                newEnemy.active = true;
                enemies.push_back(newEnemy);
                spawnCooldown = spawnRate;
                spawnCount++;
            }
            
            // Update enemies
            for (auto& enemy : enemies) {
                enemy.Update();
            }
            
            // Remove inactive enemies
            enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](Enemy& e) { return !e.active; }), enemies.end());   
        
            // Update spawn position to random x
            if (spawnCount >= maxEnemies && enemies.empty()){
                Move(GetRandomValue(0, GetScreenWidth() - 30), position.y);
                spawnCount = 0;
            }
        }

        void Draw(){
            for(auto& enemy : enemies){
                enemy.Draw();
            }
        }

        void Move(float x, float y){
            position.x = x;
            position.y = y;
        }
    };

    class CollisionSystem{
        public:
            static void CheckCollisionPlayerEnemy(Player& player, vector<Enemy>& enemies){
                for(auto& enemy : enemies){
                    if(CheckCollisionRecs(player.collision, enemy.collision)){
                        player.OnCollision();
                        enemy.OnCollision();
                        std::cout << "Collision Detected!" << std::endl;
                    }
                }
            }

            static void CheckCollisionBulletEnemy(vector<Bullet>& bullets, vector<Enemy>& enemies){
                for(auto& bullet : bullets){
                    for(auto& enemy : enemies){
                        if(CheckCollisionRecs(bullet.collision, enemy.collision)){
                            bullet.OnCollision();
                            enemy.OnCollision();
                            std::cout << "Bullet hit Enemy!" << std::endl;
                        }
                    }
                }
            }
    };
class UISystem{
    public:
        bool isGameOver;
        GameState* gameState;

        UISystem(GameState* gs){
            isGameOver = false;
            gameState = gs;
        }

        void Draw(){
            // TODO: Add placeholder for UI elements like health bar, score, etc.
            DrawText("Health: ", 10, 10, 20, BLACK);
            DrawText(TextFormat("Score : %i", gameState->score), 10, 40, 20, BLACK);

            if(isGameOver){
                const char* msg = "GAME OVER!";
                int fontSize = 40;
                int textWidth = MeasureText(msg, fontSize);
                DrawText(msg,
                    GetScreenWidth()/2 - textWidth/2,
                    GetScreenHeight()/2 - fontSize/2,
                    fontSize, BLACK);
            }
        }
};
    
int main() {
    InitWindow(600, 900, "Jet Game");
    SetTargetFPS(60);
    GameState gameState;
    EventSystem eventSystem;
    Player player = Player(25, 40, GetScreenWidth() / 2, GetScreenHeight() / 2, &eventSystem);
    Spawner spawner = Spawner(GetScreenWidth() / 2 - 15, -30, &eventSystem);
    UISystem ui = UISystem(&gameState);
    gameState.RegisterEvents(&eventSystem);

    std::cout << "Initial Player Position : " << player.position.x << ", " << player.position.y << std::endl;
    
    while (!WindowShouldClose()) {
        if (!ui.isGameOver){
            // Update game state
            player.Update();
            spawner.Update();
            
            // Check collisions
            CollisionSystem::CheckCollisionPlayerEnemy(player, spawner.enemies);
            CollisionSystem::CheckCollisionBulletEnemy(player.bullets, spawner.enemies);            
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw game elements
        player.Draw();
        spawner.Draw();
        
        ui.Draw();
        EndDrawing();
    }        
    CloseWindow();
    return 0;                                                                                                                                                              
}
    
    
    
    
