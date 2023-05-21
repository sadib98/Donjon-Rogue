#include <stdio.h>
#include <stdlib.h>
#include "../include/Extra-functions.h"

int random_min_max(int min, int max){
    return rand() % (max - min + 1) + min;
}

int manhattan_distance(int i1, int j1, int i2, int j2) {
    return abs(i1 - i2) + abs(j1 - j2);
}

int inclusion_test(int a, int b, int toTest){
    if(a <= toTest && toTest <= b)
        return 1;
    return 0;
}

void save_game(void *data){
    int *seed = (int*) data;
    FILE *fptr;

    if((fptr = fopen("savedgame.bin", "wb+")) == NULL){
        printf("Error! opening file");
        exit(1);
    }

    fwrite(seed, sizeof(int), 1, fptr);
    fclose(fptr);
    exit(1);
}

int load_game(int *seed){
    FILE *fptr;
    if((fptr = fopen("savedgame.bin", "rb")) == NULL){
        return 0;
    }
    fread(seed, sizeof(int), 1, fptr);
    fclose(fptr);
    return 1;
}