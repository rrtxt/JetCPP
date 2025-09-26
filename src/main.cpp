#include "raylib.h"
#include "raymath.h"
#include "iostream"

const int VELOCITY = 5;
const int TIMESCALE = 1;

class Player{
    public:
        Vector2 position;
        int width;
        int height;
        Player(float x , float y){
            position.x = x;
            position.y = y;
            width = 20;
            height = 30;
        }

        void Update(){
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
                position.y -= 1 * VELOCITY * TIMESCALE;
            }
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
                position.y += 1 * VELOCITY * TIMESCALE;
            }
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                position.x += 1 * VELOCITY * TIMESCALE;
            }
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                position.x -= 1 * VELOCITY * TIMESCALE;
            }

                position.x = Clamp(position.x, 0, GetScreenWidth() - width);
                position.y = Clamp(position.y, 0, GetScreenHeight() - height);
            }

            void Draw(){
                DrawRectangle(position.x, position.y, width, height, RED);
        }
    };
    
    
    int main() {
        InitWindow(600, 900, "Jet Game");
        SetTargetFPS(60);
        Player player = Player(GetScreenWidth() / 2, GetScreenHeight() / 2);
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




