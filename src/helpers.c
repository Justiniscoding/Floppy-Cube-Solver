#include "helpers.h"

int* fillNumberArray(const int length, int value){
    int array[length];
    for(int i = 0; i < length; i++){
        array[i] = value;
    }
    return array;
}