#include <math.h>

#include "raylib.h"
#include "floppy.h"

const int screenWidth = 800;
const int screenHeight = 450;

FloppyCube floppy;

void setup(){
    floppy = CreateFloppyCube();
}

int main(){
    setup();

    InitWindow(screenWidth, screenHeight, "Floppy Cube Solver");

    SetTargetFPS(60);

    Vector3 cubePos = {0, 0, 0};

    Camera3D camera = {0};

    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;       

    float frame;

    while(!WindowShouldClose()){
        frame += 0.05;

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        BeginMode3D(camera);
        DrawCube(cubePos, 2.0, 2.0, 2.0, GREEN);
        DrawCubeWires(cubePos, 2.0, 2.0, 2.0, MAROON);
        EndMode3D();

        EndDrawing();

        
    }

    CloseWindow();
}