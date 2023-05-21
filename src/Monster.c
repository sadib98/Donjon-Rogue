#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/Monster.h"

void monster_init(Monster *monster, int hp, int atk){
    (*monster).hp = hp;
    (*monster).atk = atk;
}

void monster_update_hp(Monster *monster, int points){
    int newPoints = monster->hp + points;
    if(newPoints > 0)
        (*monster).hp = newPoints;
    else
        (*monster).hp = 0;
}


void monster_update_atk(Monster *monster, int points){
    int newPoints = monster->atk + points; 
    if(newPoints > 0)
        (*monster).atk = newPoints;
    else
        (*monster).atk = 0;
}
