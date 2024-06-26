#include <math.h>
#include <time.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h" 
#include "floppy.h"
#include "moves.h"

const int screenWidth = 800;
const int screenHeight = 450;

FloppyCube floppy;

void setup(){
    srand(time(NULL)); 

    floppy = InitFloppyCube(floppy);

    // moveList = CreateMoveList(10);
}

int main(){
    setup();

    InitWindow(screenWidth, screenHeight, "Floppy Cube Solver");

    SetTargetFPS(60);

    Vector3 cubePos = {0, 0, 0};

    Camera3D camera = {0};

    camera.position = (Vector3){10.0f, 10.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;       

    float frame;
    float angle = 0;

    while(!WindowShouldClose()){
        frame += 0.05;

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        BeginMode3D(camera);
        floppy = DrawFloppyCube(floppy);
        EndMode3D();

        DrawFPS(10,10);

        Vector2 screenPosition = GetWorldToScreen((Vector3){2.0, 2.0, 0.0}, camera);
        DrawText("R", screenPosition.x, screenPosition.y, 20, BLACK);
        screenPosition = GetWorldToScreen((Vector3){-2.0, 2.0, 0.0}, camera);
        DrawText("L", screenPosition.x, screenPosition.y, 20, BLACK);
        screenPosition = GetWorldToScreen((Vector3){0.0, 2.0, 2.0}, camera);
        DrawText("F", screenPosition.x, screenPosition.y, 20, BLACK);
        screenPosition = GetWorldToScreen((Vector3){0.0, 2.0, -2.0}, camera);
        DrawText("B", screenPosition.x, screenPosition.y, 20, BLACK);

        EndDrawing();
        
        // camera.position.y = sin(frame/2.0) * 10.0;

        if(IsKeyDown(KEY_LEFT)){
            angle += 0.03;
            camera.position.x = 20*sin(angle);
            camera.position.z = 20*cos(angle);
        }else if(IsKeyDown(KEY_RIGHT)){
            angle -= 0.03;
            camera.position.x = 20*sin(angle);
            camera.position.z = 20*cos(angle);
        }else if(IsKeyDown(KEY_UP)){
            camera.position.y += 0.3;
        }else if(IsKeyDown(KEY_DOWN)){
            camera.position.y -= 0.3;
        }

        if(IsKeyReleased(KEY_F)){
            /*floppy = */DoTurn(floppy, F);
        }
        if(IsKeyReleased(KEY_R)){
            /*floppy = */DoTurn(floppy, R);
        }
        if(IsKeyReleased(KEY_L)){
            /*floppy = */DoTurn(floppy, L);
        }
        if(IsKeyReleased(KEY_B)){
            // /*floppy =*/ DoTurn(floppy, B);
            
            floppy = SolveCube(floppy);
        }

        if(GuiButton((Rectangle){ 155, 375, 150, 75 }, "Solve")){
            floppy = SolveCube(floppy);
            // printf("hello world");
        }
        if(GuiButton((Rectangle){ 0, 375, 150, 75 }, "Scramble")){
            floppy = RandomScramble(floppy);
        }
    }

    CloseWindow();
}