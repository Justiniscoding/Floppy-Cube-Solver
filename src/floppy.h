#ifndef FLOPPY
#define FLOPPY

struct _FloppyCube{
    int topFace[8];
    int bottomFace[8];
    int leftFace[2];
    int frontFace[2];
    int rightFace[2];
    int backFace[2];
};

typedef struct _FloppyCube FloppyCube;

enum _Colors{
    WHITE,
    BLUE,
    ORANGE, 
    GREEN,
    RED,
    YELLOW
};

typedef enum _Colors Colors;

FloppyCube CreateFloppyCube();

void DrawFloppyCube(FloppyCube floppyCube);

#endif