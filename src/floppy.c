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

void DrawFloppyCube(FloppyCube floppyCube){
    Vector2 planeSize = {1.9, 1.9};

    float planeOffset = 0.005;

    // Black centre area
    DrawCube((Vector3){0.0,0.0,0.0}, 6.0, 2.0, 6.0, BLACK);

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

        DrawPlane((Vector3){pos.x,planeOffset+1.0,pos.y}, planeSize, GetColorFromIndex(floppyCube.topFace[index]));

        rlPushMatrix();
        rlRotatef(180, 0, 0, -1);
        rlRotatef(180, 0, 1, 0);
        DrawPlane((Vector3){pos.x,planeOffset+1.0,pos.y}, planeSize, GetColorFromIndex(floppyCube.bottomFace[index]));
        rlPopMatrix();
    }

    // Green stickers
    rlPushMatrix();
    rlRotatef(90, 1, 0, 0);
    DrawPlane((Vector3){-2,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.frontFace[0]));
    DrawPlane((Vector3){0,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.frontFace[1]));
    DrawPlane((Vector3){2,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.frontFace[2]));
    rlPopMatrix();

    // Red stickers
    rlPushMatrix();
    rlRotatef(-90, 0, 0, 1);
    DrawPlane((Vector3){0,3+planeOffset,2}, planeSize, GetColorFromIndex(floppyCube.rightFace[0]));
    DrawPlane((Vector3){0,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.rightFace[1]));
    DrawPlane((Vector3){0,3+planeOffset,-2}, planeSize, GetColorFromIndex(floppyCube.rightFace[2]));
    rlPopMatrix();

    // Orange stickers
    rlPushMatrix();
    rlRotatef(90, 0, 0, 1);
    DrawPlane((Vector3){0,3+planeOffset,-2}, planeSize, GetColorFromIndex(floppyCube.leftFace[0]));
    DrawPlane((Vector3){0,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.leftFace[1]));
    DrawPlane((Vector3){0,3+planeOffset,2}, planeSize, GetColorFromIndex(floppyCube.leftFace[2]));
    rlPopMatrix();

    // Blue stickers
    rlPushMatrix();
    rlRotatef(-90, 1, 0, 0);
    DrawPlane((Vector3){2,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.backFace[0]));
    DrawPlane((Vector3){0,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.backFace[1]));
    DrawPlane((Vector3){-2,3+planeOffset,0}, planeSize, GetColorFromIndex(floppyCube.backFace[2]));
    rlPopMatrix();
}

FloppyCube ExecuteTurn(FloppyCube cube, int turn){
    if(turn == F){
        ValueSwap(cube.topFace, 5, cube.bottomFace, 2);
        ValueSwap(cube.topFace, 6, cube.bottomFace, 1);
        ValueSwap(cube.topFace, 7, cube.bottomFace, 0);
        ValueSwap(cube.leftFace, 2, cube.rightFace, 0);
    }
    if(turn == R){
        ValueSwap(cube.topFace, 2, cube.bottomFace, 2);
        ValueSwap(cube.topFace, 4, cube.bottomFace, 4);
        ValueSwap(cube.topFace, 7, cube.bottomFace, 7);
        ValueSwap(cube.frontFace, 2, cube.backFace, 0);
    }
    if(turn == L){
        ValueSwap(cube.topFace, 0, cube.bottomFace, 0);
        ValueSwap(cube.topFace, 3, cube.bottomFace, 3);
        ValueSwap(cube.topFace, 5, cube.bottomFace, 5);
        ValueSwap(cube.frontFace, 0, cube.backFace, 2);
    }
    if(turn == B){
        ValueSwap(cube.topFace, 0, cube.bottomFace, 7);
        ValueSwap(cube.topFace, 1, cube.bottomFace, 6);
        ValueSwap(cube.topFace, 2, cube.bottomFace, 5);
        ValueSwap(cube.leftFace, 0, cube.rightFace, 2);
    }

    return cube;
}