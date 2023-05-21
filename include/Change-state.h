#ifndef __CHANGE_STATE__
#define __CHANGE_STATE__
    #include "Player.h"
    #include "Ground.h"
    #include "Graphic-Interface.h"
    #include "Create-objects.h"
    #include "Put-objects.h"
    
    /* typedef struct stage{
        Cell **ground;
        int stage;
        struct stage *next;
    }Stage; */

    void change_stage(Cell **ground, int *actual_stage, Player *player, Coordinates *focus, int lines, int columns);

#endif