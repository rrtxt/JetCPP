#include "raylib.h"

int main() {
    InitWindow(800, 600, "Hello Raylib");
    SetTargetFPS(60);
    const int SCREEN_WIDTH = GetScreenWidth();
    const int SCREEN_HEIGHT = GetScreenHeight();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 50, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
