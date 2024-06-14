#include "moves.h"

int* CreateMoveList(const int length){
    int moveList[length];
    return moveList;
}

int* AddToMoveList(int* movelist, int move){
    int moveListIndex = 0;

    for(int i = 0; i < sizeof(&movelist)/sizeof(int); i++){
        if(movelist[i] != 0){
            moveListIndex = i+1;
        }
    }

    movelist[moveListIndex] = move+1;

    return movelist;
}

int* ShiftMoveList(int* movelist){
    for(int i = 1; i < sizeof(&movelist)/sizeof(int); i++){
        movelist[i-1] = movelist[i];
    }

    return movelist;
}

FloppyCube SolveCube(FloppyCube cube){
    int turns[7];
    FillNumberArray(turns, 7, -1);

    FloppyCube clone;

    for(int i = 0; i < 21844; i++){
        turns[0]++;
        for(int j = 0; j < 6; j++){
            if(turns[j] == 4){
                turns[j+1]++;
                turns[j] = 0;
            }
        }

        clone = CloneFloppyCube(cube, clone);

        for(int j = 0; j < 7; j++){
            clone = ExecuteTurn(clone, turns[j]);
        }
        if(IsCubeSolved(clone)){
            DoTurn(cube, turns[0]);
            DoTurn(cube, turns[1]);
            DoTurn(cube, turns[2]);
            DoTurn(cube, turns[3]);
            DoTurn(cube, turns[4]);
            DoTurn(cube, turns[5]);
            DoTurn(cube, turns[6]);
            return cube;
        }
    }

    return cube;
}