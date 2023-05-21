#include <stdio.h>
#include <stdlib.h>
#include "../include/Put-objects.h"

void put_walls(int lines, int columns, Cell **ground){
    int i, j;
    for(i = 0; i < lines; i++){
        for(j = 0; j < columns; j++){
            put_on_ground(ground, create_wall(i, j));
        }
    }
}

void put_stair_up(int lines, int columns, Cell **ground){
    put_on_ground(ground, create_stair_up(lines / 2, columns / 2));
}

void put_player(int lines, int columns, Cell **ground, Player *player){
    int i, j;
    int found;

    found = 0;
    for(i = 0; i < lines; i++){
        for(j = 0; j < columns; j++){
            if(ground[i][j].type == ROOM){
                found = 1;
                break;
            }
        }
        if(found)
            break;
    }

    (*player).pos_x = j;
    (*player).pos_y = i;
}

static void place_treasure(int lines, int columns, Cell **ground, int player_level){
    Cell room_cell;
    Cell treasure;
    int i, j, total_eligible_cell, count_neighbors;
    int rand_n, n;

    total_eligible_cell = 0;
    for(i = 0; i < lines; i++){
        for(j = 0; j < columns; j++){
            room_cell = ground[i][j];
            if(room_cell.type == ROOM){
                count_neighbors = count_neighbors_by_type(lines, columns, ground, room_cell, WALL, 1);
                if(count_neighbors == 3){
                    total_eligible_cell += 1;
                }
            }
        }
    }

    if(total_eligible_cell > 0){
        rand_n = random_min_max(1, total_eligible_cell);
        n = 0;
        for(i = 0; i < lines; i++){
            for(j = 0; j < columns; j++){
                room_cell = ground[i][j];
                if(room_cell.type == ROOM){
                    count_neighbors = count_neighbors_by_type(lines, columns, ground, room_cell, WALL, 1);
                    if(count_neighbors == 3){
                        n += 1;
                        if(n == rand_n){
                            treasure = create_treasure(i, j, player_level);
                            ground[i][j] = treasure;
                            return;
                        }
                    }
                }
            }
        }
    }
}

void put_treasures(int lines, int columns, Cell **ground, int how_much, int player_level){
    int i;

    for(i = 0; i < how_much; i++){
        place_treasure(lines, columns, ground, player_level);
    }
}


void put_guards(int lines, int columns, Cell **ground){
    Cell monster, check_cell;

    int i, j;

    for(i = 0; i < lines; i++){
        for(j = 0; j < columns; j++){
            check_cell = ground[i][j];
            if(check_cell.type == ROOM){
                if(count_neighbors_by_type(lines, columns, ground, check_cell, TREASURE, 1) == 1){
                    monster = create_monster(i, j);
                    ground[i][j] = monster;
                }
            }
        }
    }

}


static int count_rooms(int lines, int columns, Cell **ground){
    int i, j, count;

    count = 0;
    for(i = 0; i < lines; i++){
        for(j = 0; j < columns; j++){
            if(ground[i][j].type == ROOM)
                count += 1;
        }
    }
}

void put_monster(int lines, int columns, Cell **ground){
    Cell monster;
    int rand_n, total_rooms, n, i, j;
    total_rooms = count_rooms(lines, columns, ground);

    if(total_rooms > 0){
        rand_n = random_min_max(1, count_rooms(lines, columns, ground));
        n = 0;

        for(i = 0; i < lines; i++){
            for(j = 0; j < columns; j++){
                if(ground[i][j].type == ROOM){
                    n += 1;
                    if(n == rand_n){
                        monster = create_monster(i, j);
                        ground[i][j] = monster;
                    }
                }
            }
        }
    }
}