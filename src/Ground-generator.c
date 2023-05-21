#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "math.h"
#include "../include/Ground-generator.h"

int count_neighbors_by_type(int lines, int columns, Cell **ground, Cell c, Celltype type, int distance){
    int i, j, m_dist, count;
    count = 0;
    for(i = 0; i < lines; i++){
        for(j = 0; j < columns; j++){
            m_dist = manhattan_distance( c.line, c.column, i, j);
            if((m_dist == distance) && (ground[i][j].type == type)){
                count += 1;
            }
        }
    }
    return count;
}

int eligible_cell(int lines, int columns, Cell **ground, Cell c){
    int total_rooms_distance1,total_stair_up_distance1,
    total_stair_up_distance2 , total_rooms_distance2;

    if((c.type == WALL) || (c.type == STAIR_UP)){
        total_rooms_distance1 = count_neighbors_by_type(lines, columns, ground, c, ROOM, 1);
        total_stair_up_distance1 = count_neighbors_by_type(lines, columns, ground, c, STAIR_UP, 1);
        total_rooms_distance2 = count_neighbors_by_type(lines, columns, ground, c, ROOM, 2);
        total_stair_up_distance2 = count_neighbors_by_type(lines, columns, ground, c, STAIR_UP, 2);
        
        total_rooms_distance1 += total_stair_up_distance1;
        total_rooms_distance2 += total_stair_up_distance2;

        if((total_rooms_distance1 == 1) && (total_rooms_distance2 <= 2))
            return 1;
    }
    
    return 0;
}

Cell* get_adjacents(int lines, int columns, Cell **ground, Cell cell){
    Cell *neighbors;
    int i, j, m_dis, index;
    neighbors = (Cell*)malloc(4 * sizeof(Cell));
    index = 0;
    
    for(i = 1; i < lines - 1; i++){
        for (j = 1; j < columns - 1; j++){   
            m_dis = manhattan_distance(cell.line, cell.column, i, j);
            if((m_dis == 1) && (ground[i][j].type != STAIR_UP) ){
                neighbors[index] = ground[i][j];
                index += 1;
            }
        }
    }
    return neighbors;
}

Cell* get_eligible_adjacents(int lines, int columns, Cell **ground, Cell cell, int *length){
    Cell *neighbors;
    Cell *temp_adjacents;
    int i, count;
    count = 0;
    temp_adjacents = get_adjacents(lines, columns, ground, cell);
    neighbors = (Cell*)malloc(4 * sizeof(Cell));
    
    for(i = 0; i < 4; i++){
        if(eligible_cell(lines, columns, ground, temp_adjacents[i])){
            neighbors[i] = temp_adjacents[i];
            count += 1;
        }
    }

    *length = count;
    return neighbors;
}

void make_wall_rooms_with_3walls(int lines, int columns, Cell **ground){
    int i, j;
    Cell cell_check;

    for(i = 1; i < lines - 1; i++){
        for(j = 1; j < columns - 1; j++){
            cell_check = get_cell_on_ground(ground, i, j);
            if((cell_check.type == ROOM) &&
                (count_neighbors_by_type(lines, columns, ground, cell_check, WALL, 1) == 3)){
                    cell_check.type = WALL;
                    put_on_ground(ground, cell_check);
                }
        }
    }
}

void generate_labyrinth(int lines, int columns, Cell **ground){
    Cell *toexpand;
    Cell *c_adjacents;
    Cell c;
    int toexpand_size, rand_index, c_adjacents_length;
    
    c_adjacents_length = 0;

    /* Step 1 */
    c.type = STAIR_UP;
    c.line = lines / 2;
    c.column = columns / 2;
    
    toexpand_size = 4;
    toexpand = get_adjacents(lines, columns, ground, c);
    
    while(toexpand_size != 0){
        /* Step 2 */

        rand_index = random_min_max(0, toexpand_size - 1);
        c = toexpand[rand_index];
        remove_from_list(toexpand, &toexpand_size, rand_index);

        if(eligible_cell(lines, columns, ground, c)){
            /* Step 3 */
            c.type = ROOM;
            put_on_ground(ground, c);
            
            /* Step 4 */
            c_adjacents = get_eligible_adjacents(lines, columns, ground, c, &c_adjacents_length);
            addlist_to_list(c_adjacents, toexpand, &c_adjacents_length, &toexpand_size);
        }
        
    }
    /* Step 6 */
    /* make_wall_rooms_with_3walls(lines, columns, ground); */
}