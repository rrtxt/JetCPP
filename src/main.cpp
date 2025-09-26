#include "raylib.h"

const int SCREEN_WIDTH = GetScreenWidth();
const int SCREEN_HEIGHT = GetScreenHeight();

class Player{
    public:
        Vector2 position;
        int width;
        int height;
        Player(){
            position.x = SCREEN_WIDTH/2;
            position.y = SCREEN_HEIGHT/2;
            width = 20;
            height = 30;
        }
};

const int VELOCITY = 5;
const int TIMESCALE = 1;
Player player = Player();

void InputUpdate() {
    if (IsKeyDown(KEY_UP)) {
        player.position.y -= 1 * VELOCITY * TIMESCALE;
    }
    if (IsKeyDown(KEY_DOWN)) {
        player.position.y += 1 * VELOCITY * TIMESCALE;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player.position.x += 1 * VELOCITY * TIMESCALE;
    }
    if (IsKeyDown(KEY_LEFT)) {
        player.position.x -= 1 * VELOCITY * TIMESCALE;
    }
}

void Update(){
    DrawRectangle(player.position.x, player.position.y, player.width, player.height, RED);
    InputUpdate();
}

int main() {
    InitWindow(800, 600, "Jet Game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Update();
        EndDrawing();
    }

    CloseWindow();
    return 0;                                                                                                                                                              
}




