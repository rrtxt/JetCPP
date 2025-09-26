#include "raylib.h"
#include "raymath.h"
#include "iostream"

const int VELOCITY = 200;
const int TIMESCALE = 1;

class Player{
    public:
        Vector2 position;
        Vector2 size;
        Vector2 inputDirection;
        Player(int width, int height, float x , float y){
            position.x = x;
            position.y = y;
            size.x = width;
            size.y = height;
        }

        void Update(){
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

            Vector2 velocity = Vector2Scale(inputDirection, VELOCITY * GetFrameTime() * TIMESCALE);
            position = Vector2Add(position, velocity);
        }

        void Draw(){
            DrawRectangle(position.x, position.y, size.x, size.y, RED);
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




