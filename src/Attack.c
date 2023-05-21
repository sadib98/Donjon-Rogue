#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/Attack.h"


int damage(int attribute){
    if(attribute < 1)
        return 0;
    int percent = random_min_max(80, 120);
    return percent * attribute / 100;
}

int critical_hit(int probability) {
    int rand = random_min_max(1, 100);
    if(rand > 0 && rand < probability + 1)
        return 1;
    return 0;
}

int is_dead(int hp){
    if(hp == 0)
        return 1;
    return 0;
}

int player_attack(Player *player, int mouse_x, int mouse_y, int zoom_size, Coordinates **coordinates, Coordinates focus, int lines, int columns, Cell **ground, InfoType info, int probability, int bonus_exp){
    Cell cell;
    int clicked_line, clicked_column;
    int damage_points;
    
    get_line_column_from_coordinates(mouse_x, mouse_y, &clicked_line, &clicked_column, zoom_size, coordinates);
    clicked_column = focus.x1 + clicked_column;
    clicked_line = focus.y1 + clicked_line;

    cell = ground[clicked_line][clicked_column];
    if(cell.type == MONSTER){
        if(manhattan_distance(cell.line, cell.column, (*player).pos_y, (*player).pos_x) == 1){
            
            /* Player attack */
            if(info == ATTACK){
                if(critical_hit(probability)){
                    damage_points = damage((*player).atk) * 3;
                }else{
                    damage_points = damage((*player).atk);
                }
                monster_update_hp(&(cell.entity.monster), -damage_points);
            }else if(info == MAGICAL_ATK){
                if(critical_hit(probability)){
                    damage_points = damage((*player).intel * 2) * 3;
                }else{
                    damage_points = damage((*player).intel * 2);
                }
                
                player_update_mp(player, -20);
                monster_update_hp(&(cell.entity.monster), -damage_points);
            }

            if(is_dead(cell.entity.monster.hp)){
                (*player).exp += ((cell.entity.monster.atk * 10) + ((cell.entity.monster.atk * 10) * bonus_exp / 100));
                ground[clicked_line][clicked_column].type = ROOM;
                return 1;
            }else{
                ground[clicked_line][clicked_column] = cell;
                /* Monster counter attack */
                player_update_hp(player, -damage(cell.entity.monster.atk));
                return 1;
            }
        }
    }
    return 0;
}
/*rajouter boucle combat qui augmente le nombre d'Exp quand le perso
gagne */