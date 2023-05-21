#include <stdio.h>
#include <stdlib.h>
#include "../include/Change-state.h"

void copy_ground(Cell **old_ground, Cell **new_ground, int lines, int columns){
    int i, j;
    for(i = 0; i < lines; i++){
        for(j = 0; j < columns; j++){
            old_ground[i][j].type   = new_ground[i][j].type;
            /* old_ground[i][j].entity.monster = new_ground[i][j].entity.monster;
            old_ground[i][j].entity.treasure = new_ground[i][j].entity.treasure;
            old_ground[i][j].line   = new_ground[i][j].line;
            old_ground[i][j].column = new_ground[i][j].column; */
        }
    }
}

void change_stage(Cell **ground, int *actual_stage, Player *player, Coordinates *focus, int lines, int columns){
    Cell **new_ground;
    Cell actual_cell;
    int i, j;
    actual_cell = get_cell_on_ground(ground, player->pos_y, player->pos_x);
    
    printf("stage = %d, Player=(%d, %d)\n", *actual_stage, player->pos_x, player->pos_y);
    
    switch(actual_cell.type){

        case STAIR_UP : *actual_stage += 1;
                        printf("stage = %d\n", *actual_stage);
                        new_ground = create_ground(lines, columns);
                        
                        for(i = 0; i < lines; i++){
                            for(j = 0; j < columns; j++){
                                ground[i][j].type   = new_ground[i][j].type;
                                /* old_ground[i][j].entity.monster = new_ground[i][j].entity.monster;
                                old_ground[i][j].entity.treasure = new_ground[i][j].entity.treasure;
                                old_ground[i][j].line   = new_ground[i][j].line;
                                old_ground[i][j].column = new_ground[i][j].column; */
                            }
                        }
                        for(i = 0; i < lines; i++){
                            free(new_ground[i]);
                        }
                        free(new_ground);
                        /* copy_ground(ground, create_ground(lines, columns), lines, columns); */
                        
                        put_player(lines, columns, ground, player);
                        printf("stage = %d, Player=(%d, %d)\n", *actual_stage, player->pos_x, player->pos_y);
                        get_focus_area_by_player(lines, columns, 10, focus, *player);
                        break;

        default : break;
    }

}