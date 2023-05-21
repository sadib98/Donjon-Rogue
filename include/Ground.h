#ifndef __GROUND__
#define __GROUND__
#include "Monster.h"
#include "Treasure.h"

typedef enum {
    WALL, ROOM, MONSTER, TREASURE,
    STAIR_UP, STAIR_DOWN
} Celltype;

typedef union entity {
    Monster monster;
    Treasure treasure;
} Entity;


typedef struct {
    Celltype type;
    Entity entity;
    int line;
    int column;
} Cell;


void put_on_ground(Cell **ground, Cell newCell);
Cell get_cell_on_ground(Cell **ground, int on_line, int on_column);

#endif