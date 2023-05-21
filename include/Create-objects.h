#ifndef __CREATE_OBJECTS__
#define __CREATE_OBJECTS__
    #include "Player.h"
    #include "Monster.h"
    #include "Treasure.h"
    #include "Ground.h"
    #include "Ground-generator.h"
    #include "Put-objects.h"

    Player create_player();

    Cell create_monster(int line, int column);

    Cell create_treasure(int line, int column, int level);

    Cell create_wall(int line, int column);

    Cell create_stair_up(int line, int column);

    /* Function returns an array of type Cell of size (lines * columns). */
    Cell** create_ground(int lines, int columns);
#endif