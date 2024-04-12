#include "helpers.h"

int* FillNumberArray(int* array, const int length, int value){
    for(int i = 0; i < length; i++){
        array[i] = value;
    }
    return array;
}

Color GetColorFromIndex(int index){
    Color color;
    color.a = 0xff;
    switch (index){
        case CWHITE:
            color.r = 0xff;
            color.g = 0xff;
            color.b = 0xff;
            break;
        case CBLUE:
            color.r = 0x35;
            color.g = 0x79;
            color.b = 0xde;
            break;
        case CORANGE:
            color.r = 0xee;
            color.g = 0x67;
            color.b = 0x02;
            break;
        case CGREEN:
            color.r = 0x2a;
            color.g = 0xbb;
            color.b = 0x2a;
            break;
        case CRED:
            color.r = 0xc7;
            color.g = 0x24;
            color.b = 0x2f;
            break;
        case CYELLOW:
            color.r = 0xff;
            color.g = 0xdd;
            color.b = 0x00;
            break;
        default:
            break;
    };
    return color;
}

void ValueSwap(int* array1, int index1, int* array2, int index2){
    int temp = array1[index1];

    array1[index1] = array2[index2];
    array2[index2] = temp;
}

int RandomRange(int max){
    int divisor = RAND_MAX/(max+1);
    int num;

    do{ 
        num = rand() / divisor;
    }while (num > max);

    return num;
}