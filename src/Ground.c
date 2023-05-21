#include <stdio.h>
#include <stdlib.h>
#include "../include/Ground.h"

void put_on_ground(Cell **ground, Cell newCell){
        ground[newCell.line][newCell.column] = newCell;
}

Cell get_cell_on_ground(Cell **ground, int on_line, int on_column){
    return ground[on_line][on_column];
}
