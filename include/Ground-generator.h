#ifndef __GROUND_GENERATOR__
#define __GROUND_GENERATOR__
#include "Extra-functions.h"
#include "List-manager.h"
#include "Ground.h"

int count_neighbors_by_type(int lines, int columns, Cell **ground, Cell c, Celltype type, int distance);

void generate_labyrinth(int lines, int columns, Cell **ground);

#endif