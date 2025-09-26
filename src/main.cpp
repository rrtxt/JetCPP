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
        float speed;
        int width;
        int height;
        bool active;
        Bullet(float x, float y){
            position.x = x;
            position.y = y;
            speed = 300;
            width = 5;
            height = 10;
        }
        void Update(){
            if(active){
                // Move upward
                position.y -= speed * GetFrameTime();
                
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
        std::vector<Bullet> bullets;
        Player(int width, int height, float x , float y){
            position.x = x;
            position.y = y;
            size.x = width;
            size.y = height;
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

            // Shooting
            if (IsKeyPressed(KEY_SPACE)) {
                Bullet newBullet(position.x + size.x / 2 - 2.5f, position.y);
                newBullet.active = true;
                bullets.push_back(newBullet);
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
        }

        void Draw(){
            DrawRectangle(position.x, position.y, size.x, size.y, RED);
            for(auto& bullet : bullets){
                bullet.Draw();
            }
        }
    };

    
    
int main() {
    InitWindow(600, 900, "Jet Game");
    SetTargetFPS(60);
    Player player = Player(25, 40, GetScreenWidth() / 2, GetScreenHeight() / 2);
    std::cout << "Initial Player Position : " << player.position.x << ", " << player.position.y << std::endl;
    
    while (!WindowShouldClose()) {
        player.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        player.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;                                                                                                                                                              
}




