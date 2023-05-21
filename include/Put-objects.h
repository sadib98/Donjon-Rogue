#ifndef __PUT_OBJECTS__
#define __PUT_OBJECTS__
    #include "Extra-functions.h"
    #include "Ground.h"
    #include "Create-objects.h"
    
    void put_walls(int lines, int columns, Cell **ground);

    void put_stair_up(int lines, int columns, Cell **ground);

    void put_player(int lines, int columns, Cell **ground, Player *player);

    void put_treasures(int lines, int columns, Cell **ground, int how_much, int player_level);

    void put_guards(int lines, int columns, Cell **ground);

    void put_monster(int lines, int columns, Cell **ground);
#endif