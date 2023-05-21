#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/Treasure.h"

void init_treasure(Treasure *T, int level){
    (*T).objects = malloc(T->total * sizeof(Object));

    (*T).objects[0].type = random_min_max(CARE, LEARNING);
    
    (*T).objects[1].type = ARMOR;
    (*T).objects[1].value = random_min_max(1, level);
    
    (*T).objects[2].type = WEAPON;
    (*T).objects[2].value = random_min_max(1, level);
    
    (*T).objects[3].type = WAND;
    (*T).objects[3].value = random_min_max(1, level);
}