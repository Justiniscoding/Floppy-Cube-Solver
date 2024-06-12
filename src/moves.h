#ifndef FLOPPYSOLVER_MOVES
#define FLOPPYSOLVER_MOVES

#include <stdio.h>
#include "helpers.h"
#include "floppy.h"

int* CreateMoveList(const int length);
int* AddToMoveList(int* movelist, int move);
int* ShiftMoveList(int* movelist);
FloppyCube SolveCube(FloppyCube cube);

#endif