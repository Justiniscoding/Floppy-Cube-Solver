#ifndef HELPERS
#define HELPERS

#include "raylib.h"
#include "string.h"
#include "floppy.h"

Color GetColorFromIndex(int index);

int RandomRange(int max);

int* FillNumberArray(int* array, const int length, int value);

void ValueSwap(int* array1, int index1, int* array2, int index2);

#endif