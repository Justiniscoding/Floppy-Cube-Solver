#ifndef FLOPPY
#define FLOPPY

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "helpers.h"
#include "raylib.h"
#include "rlgl.h"

struct _FloppyCube{
    int topFace[8];
    int bottomFace[8];
    int leftFace[3];
    int frontFace[3];
    int rightFace[3];
    int backFace[3];
};

typedef struct _FloppyCube FloppyCube;

enum _Colors{
    CWHITE,
    CBLUE,
    CORANGE, 
    CGREEN,
    CRED,
    CYELLOW
};

typedef enum _Colors Colors;

enum _Turns{
    R,
    F,
    L,
    B
};

typedef enum _Turns Turns;

void DrawFloppyCube(FloppyCube floppyCube);

FloppyCube RandomScramble(FloppyCube cube);
FloppyCube InitFloppyCube(FloppyCube floppyCube);
FloppyCube ExecuteTurn(FloppyCube cube, int turn);

#endif