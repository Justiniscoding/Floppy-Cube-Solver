#include "floppy.h"

FloppyCube InitFloppyCube(FloppyCube floppyCube){
    FillNumberArray(floppyCube.topFace, 8, CWHITE);
    FillNumberArray(floppyCube.bottomFace, 8, CYELLOW);
    FillNumberArray(floppyCube.leftFace, 3, CORANGE);
    FillNumberArray(floppyCube.frontFace, 3, CGREEN);
    FillNumberArray(floppyCube.rightFace, 3, CRED);
    FillNumberArray(floppyCube.backFace, 3, CBLUE);

    return floppyCube;
}

float progress = 0;
int fRotating = 0;
int rRotating = 0;
int lRotating = 0;
int bRotating = 0;

int animSpeed = 4;

FloppyCube DrawFloppyCube(FloppyCube floppyCube){
    if(fRotating || rRotating || lRotating || bRotating){
        progress += animSpeed;
    }
    if(progress >= 180){
        progress = 0;
        if(fRotating){
            floppyCube = ExecuteTurn(floppyCube, F);
            fRotating = 0;
        }
        if(rRotating){
            floppyCube = ExecuteTurn(floppyCube, R);
            rRotating = 0;
        }
        if(lRotating){
            floppyCube = ExecuteTurn(floppyCube, L);
            lRotating = 0;
        }
        if(bRotating){
            floppyCube = ExecuteTurn(floppyCube, B);
            bRotating = 0;
        }
    }
    Vector2 planeSize = {1.85, 1.85};

    float planeOffset = 0.005;

    // Black centre area
    for(int i = 0; i < 9; i++){
        Vector3 pos = {0.0, 0.0, 0.0};

        pos.x = (i % 3 - 1) * 2.0;
        pos.z = floor(i / 3.0) * 2.0 - 2.0;

        if(fRotating && pos.z == 2){
            continue;
        }

        if(rRotating && pos.x == 2){
            continue;
        }

        if(lRotating && pos.x == -2){
            continue;
        }

        if(bRotating && pos.z == -2){
            continue;
        }

        DrawCube(pos, 2.0, 2.0, 2.0, BLACK);
    }

    // White and yellow stickers
    DrawPlane((Vector3){0.0,planeOffset+1.0,0.0}, planeSize, WHITE);

    rlPushMatrix();
    rlRotatef(180, 0, 0, 1);
    DrawPlane((Vector3){0.0,planeOffset+1.0,0.0}, planeSize, GetColorFromIndex(CYELLOW));
    rlPopMatrix();
    
    for(int i = 0; i < 8; i++){
        Vector2 pos = {0.0, 0.0};
        if(i != 4){
            pos.x = (i % 3 - 1) * 2.0;
            pos.y = floor(i / 3.0) * 2.0 - 2.0;
        }else{
            pos.x = 2.0;
            pos.y = 2.0;
        }

        int index = i;

        if(index == 4){
            index = 7;
        }else if(index > 4){
            index--;
        }

        rlPushMatrix();
        if(i > 3 && i != 5 && fRotating){
            rlRotatef(progress, 0, 0, 1);
        }
        if(rRotating && (index == 2 || index == 4 || index == 7)){
            rlRotatef(progress, 1, 0, 0);
        }
        if(lRotating && (index == 0 || index == 3 || index == 5)){
            rlRotatef(progress, 1, 0, 0);
        }
        if(bRotating && index < 3){
            rlRotatef(progress, 0, 0, 1);
        }
        DrawPlane((Vector3){pos.x,planeOffset+1.0,pos.y}, planeSize, GetColorFromIndex(floppyCube.topFace[index]));
        rlPopMatrix();

        rlPushMatrix();
        rlRotatef(180, 0, 0, -1);
        rlRotatef(180, 0, 1, 0);
        if(i < 3 && fRotating){
            rlRotatef(progress, 0, 0, -1);
        }
        if(bRotating && index > 4){
            rlRotatef(progress, 0, 0, -1);
        }
        if(rRotating && (index == 2 || index == 4 || index == 7)){
            rlRotatef(progress, 1, 0, 0);
        }
        if(lRotating && (index == 0 || index == 3 || index == 5)){
            rlRotatef(progress, 1, 0, 0);
        }
        DrawPlane((Vector3){pos.x,planeOffset+1.0,pos.y}, planeSize, GetColorFromIndex(floppyCube.bottomFace[index]));
        rlPopMatrix();
    }

    // Green stickers
    rlPushMatrix();
    rlRotatef(90, 1, 0, 0);
    if(fRotating){
        rlRotatef(progress, 0, 1, 0);
    }
    if(lRotating){
        rlRotatef(progress, 1, 0, 0);
    }
    DrawPlane((Vector3){-2,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.frontFace[0]));

    if(fRotating){
        DrawCube((Vector3){2, 2, 0}, 2.0, 2.0, 2.0, BLACK);
        DrawCube((Vector3){0, 2, 0}, 2.0, 2.0, 2.0, BLACK);
        DrawCube((Vector3){-2, 2, 0}, 2.0, 2.0, 2.0, BLACK);
    }

    if(lRotating){
        rlRotatef(progress, -1, 0, 0);
    }
    DrawPlane((Vector3){0,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.frontFace[1]));
    if(rRotating){
        rlRotatef(progress, 1, 0, 0);
    }
    DrawPlane((Vector3){2,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.frontFace[2]));
    rlPopMatrix();

    // Red stickers
    rlPushMatrix();
    rlRotatef(-90, 0, 0, 1);
    if(rRotating){
        rlRotatef(progress, 0, 1, 0);
    }
    if(fRotating){
        rlRotatef(progress, 0, 0, 1);
    }
    DrawPlane((Vector3){0,3+planeOffset,2}, planeSize, GetColorFromIndex(floppyCube.rightFace[0]));

    if(rRotating){
        DrawCube((Vector3){0, 2, 2}, 2.0, 2.0, 2.0, BLACK);
        DrawCube((Vector3){0, 2, 0}, 2.0, 2.0, 2.0, BLACK);
        DrawCube((Vector3){0, 2, -2}, 2.0, 2.0, 2.0, BLACK);
    }

    if(fRotating){
        rlRotatef(progress, 0, 0, -1);
    }
    DrawPlane((Vector3){0,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.rightFace[1]));
    if(bRotating){
        rlRotatef(progress, 0, 0, 1);
    }
    DrawPlane((Vector3){0,3+planeOffset,-2}, planeSize, GetColorFromIndex(floppyCube.rightFace[2]));
    rlPopMatrix();

    // Orange stickers
    rlPushMatrix();
    rlRotatef(90, 0, 0, 1);
    if(lRotating){
        rlRotatef(progress, 0, -1, 0);
    }
    if(bRotating){
        rlRotatef(progress, 0, 0, 1);
    }
    DrawPlane((Vector3){0,3+planeOffset,-2}, planeSize, GetColorFromIndex(floppyCube.leftFace[0]));

    if(lRotating){
        DrawCube((Vector3){0, 2, 2}, 2.0, 2.0, 2.0, BLACK);
        DrawCube((Vector3){0, 2, 0}, 2.0, 2.0, 2.0, BLACK);
        DrawCube((Vector3){0, 2, -2}, 2.0, 2.0, 2.0, BLACK);
    }

    if(bRotating){
        rlRotatef(progress, 0, 0, -1);
    }
    DrawPlane((Vector3){0,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.leftFace[1]));
    if(fRotating){
        rlRotatef(progress, 0, 0, 1);
    }
    DrawPlane((Vector3){0,3+planeOffset,2}, planeSize, GetColorFromIndex(floppyCube.leftFace[2]));
    rlPopMatrix();

    // Blue stickers
    rlPushMatrix();
    rlRotatef(-90, 1, 0, 0);
    if(bRotating){
        rlRotatef(progress, 0, -1, 0);
    }
    if(rRotating){
        rlRotatef(progress, 1, 0, 0);
    }
    DrawPlane((Vector3){2,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.backFace[0]));

    if(bRotating){
        DrawCube((Vector3){2, 2, 0}, 2.0, 2.0, 2.0, BLACK);
        DrawCube((Vector3){-2, 2, 0}, 2.0, 2.0, 2.0, BLACK);
        DrawCube((Vector3){0, 2, 0}, 2.0, 2.0, 2.0, BLACK);
    }

    if(rRotating){
        rlRotatef(progress, -1, 0, 0);
    }
    DrawPlane((Vector3){0,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.backFace[1]));
    if(lRotating){
        rlRotatef(progress, 1, 0, 0);
    }
    DrawPlane((Vector3){-2,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.backFace[2]));
    rlPopMatrix();

    return floppyCube;
}

FloppyCube ExecuteTurn(FloppyCube cube, int turn){
    if(turn == F){
        ValueSwap(cube.topFace, 5, cube.bottomFace, 2);
        ValueSwap(cube.topFace, 6, cube.bottomFace, 1);
        ValueSwap(cube.topFace, 7, cube.bottomFace, 0);
        ValueSwap(cube.leftFace, 2, cube.rightFace, 0);
        ValueSwap(cube.frontFace, 2, cube.frontFace, 0);
    }
    if(turn == R){
        ValueSwap(cube.topFace, 2, cube.bottomFace, 2);
        ValueSwap(cube.topFace, 4, cube.bottomFace, 4);
        ValueSwap(cube.topFace, 7, cube.bottomFace, 7);
        ValueSwap(cube.frontFace, 2, cube.backFace, 0);
        ValueSwap(cube.rightFace, 2, cube.rightFace, 0);
    }
    if(turn == L){
        ValueSwap(cube.topFace, 0, cube.bottomFace, 0);
        ValueSwap(cube.topFace, 3, cube.bottomFace, 3);
        ValueSwap(cube.topFace, 5, cube.bottomFace, 5);
        ValueSwap(cube.frontFace, 0, cube.backFace, 2);
        ValueSwap(cube.leftFace, 2, cube.leftFace, 0);
    }
    if(turn == B){
        ValueSwap(cube.topFace, 0, cube.bottomFace, 7);
        ValueSwap(cube.topFace, 1, cube.bottomFace, 6);
        ValueSwap(cube.topFace, 2, cube.bottomFace, 5);
        ValueSwap(cube.leftFace, 0, cube.rightFace, 2);
        ValueSwap(cube.backFace, 0, cube.backFace, 2);
    }

    return cube;
}

void DoTurn(FloppyCube cube, int turn){
    if(turn == F){
        fRotating = 1;
    }
    if(turn == B){
        bRotating = 1;
    }
    if(turn == R){
        rRotating = 1;
    }
    if(turn == L){
        lRotating = 1;
    }
}

FloppyCube RandomScramble(FloppyCube cube){
    int previous;

    for(int i = 0; i < 7; i++){
        int num = RandomRange(3);

        while(previous == num){
            num = RandomRange(3);
        }

        cube = ExecuteTurn(cube, num);

        previous = num;
    }

    return cube;
}