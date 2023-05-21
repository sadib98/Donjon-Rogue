#include <stdio.h>
#include <stdlib.h>
#include "../include/Player.h"

void player_inventory_init(Treasure *inventory){
    int i;
    (*inventory).objects = malloc((*inventory).total * sizeof(Object));
    for(i = 0; i < (*inventory).total; i++){
        (*inventory).objects[i].type = UNAVAILABLE;
    }
}

void player_init(Player *player){
    (*player).hp = 100;
    (*player).mp = 50;
    (*player).atk = 10;
    (*player).intel = 10;
    (*player).def = 10;
    (*player).exp = 0;
    (*player).lv = 1;
    (*player).inventory.total = 12;
    player_inventory_init(&((*player).inventory));
}   

static void player_update_hp_toMax(Player *player){
    (*player).hp = player->def * 10;
}

void player_update_hp(Player *player, int points){
    int newPoints = player->hp + points;
    if(newPoints > 0)
        (*player).hp = newPoints;
    else
        (*player).hp = 0;
}

static void player_update_mp_toMax(Player *player){
    (*player).mp = 10 * player->intel - 50;
}

void player_update_mp(Player *player, int points){
    int newPoints = player->mp + points; 
    if(newPoints > 0)
        (*player).mp = newPoints;
    else
        (*player).mp = 0;
}

void player_update_atk(Player *player, int atk_points){
    int newAtk_points = player->atk + atk_points; 
    if(newAtk_points > 0)
        (*player).atk = newAtk_points;
    else
        (*player).atk = 0;
}

void player_update_intel(Player *player, int intel_points){
    int new_intel_points = player->intel + intel_points;
    if(new_intel_points > 0)
        (*player).intel = new_intel_points;
    else
        (*player).intel = 0;
}

void player_update_def(Player *player, int def_points){
    int new_def_points = player->def + def_points;
    if(new_def_points > 0)
        (*player).def = new_def_points;
    else
        (*player).def = 0;
}

void player_update_exp(Player *player, int exp_points){
    int new_exp_points = player->exp + exp_points;
    if(new_exp_points > 0)
        (*player).exp = new_exp_points;
    else
        (*player).exp = 0;
}

int player_update_lv(Player *player){
    if(player->exp >= 350 + 50 * player->lv){
        player_update_exp(player, - (350 + 50 * player->lv));
        (*player).lv += 1;
        player_update_hp_toMax(player);
        player_update_mp_toMax(player);

        return 1;
    }
    return 0;
}

void level_upgrade_points(Player *player, int option){
    switch(option){
        case 1:     player_update_atk(player, 1);
                    break;
        case 2:     player_update_intel(player, 1);
                    break;
        
        case 3:     player_update_def(player, 1);
                    break;
        
        default:    break;
    }
}

int count_inventory_object_by_type(Player player, Object_type type){
    int i, count;
    count = 0; 
    for(i = 0; i < player.inventory.total; i++){
        if(player.inventory.objects[i].type == type){
            count += 1;
        }
    }

    return count;
}

int count_inventory_potions(Player player){
    return count_inventory_object_by_type(player, CARE) + 
           count_inventory_object_by_type(player, MAGIC) +
           count_inventory_object_by_type(player, REGENERATION) + 
           count_inventory_object_by_type(player, PRECISION) +
           count_inventory_object_by_type(player, LEARNING);
}

int inventory_add_object(Player *player, Object object){
    int total_available;
    int i;

    total_available = count_inventory_object_by_type((*player), UNAVAILABLE);
    
    if(total_available > 0){
        /* Adding equipement */
        for(i = 0; i < player->inventory.total; i++){
            if(player->inventory.objects[i].type == UNAVAILABLE){
                (*player).inventory.objects[i] = object;
                break;
            }
        }

        /* Equipement effects */
        switch(object.type){
            case CARE:  player_update_hp(player, ((player->def * 10) * 10) / 100);
                        break;

            case MAGIC: player_update_mp(player, ((player->intel * 10 - 50) * 10) / 100);
                        break;
            case ARMOR: (*player).def += object.value;
                        break;

            case WEAPON: (*player).atk += object.value;
                        break;

            case WAND: (*player).intel += object.value;
                        break;

            default:    break;
        }
        return 1;
    }

    return 0;
}

void inventory_remove_object(Player *player, Object_type type){
    int total_type, i;
    Object new_object;
    new_object.type = UNAVAILABLE;

    total_type = count_inventory_object_by_type(*player, type);

    if(total_type > 0){
        for(i = 0; i < player->inventory.total; i++){
            if(player->inventory.objects[i].type == type){
                (*player).inventory.objects[i] = new_object;
                break;
            }
        }
    }
}

void inventory_remove_potion(Player *player){
    int i;
    for(i = 0; i < player->inventory.total; i++){
        switch(player->inventory.objects[i].type){
            case CARE:  inventory_remove_object(player, CARE);
                        return;
            case MAGIC: inventory_remove_object(player, MAGIC);
                        return;
            case REGENERATION:  inventory_remove_object(player, REGENERATION);
                                return;
            case PRECISION: inventory_remove_object(player, PRECISION);
                            return;
            case LEARNING:  inventory_remove_object(player, LEARNING);
                            return;

            default:    break;
        }
    }
}

void inventory_remove_by_option(Player *player, int option){
    switch(option){
        case 1: inventory_remove_potion(player);
                break;

        case 2: inventory_remove_object(player, ARMOR);
                break;

        case 3: inventory_remove_object(player, WEAPON);
                break;

        case 4: inventory_remove_object(player, WAND);
                break;

        default:    break;
    }
}

static int disappear_treasure(Treasure treasures){
    int i, count;
    count = 0;
    for(i = 0; i < treasures.total; i++){
        if(treasures.objects[i].type == UNAVAILABLE)
            count += 1;
    }

    if(count == treasures.total)
        return 1;
    return 0;
}

void inventory_add_by_option(Cell **ground, Player *player, int option){
    Object rm_obj;
    Cell rm_cell;
    Treasure treasures;
    rm_cell.type = ROOM;
    rm_cell.line = player->pos_y;
    rm_cell.column = player->pos_x;


    treasures = ground[player->pos_y][player->pos_x].entity.treasure;

    switch(option){
        case 1: if(inventory_add_object(player, treasures.objects[0])){
                    rm_obj.type = UNAVAILABLE;
                    treasures.objects[0] = rm_obj;
                    if(disappear_treasure(treasures)){
                        ground[player->pos_y][player->pos_x] = rm_cell;
                    }else{
                        ground[player->pos_y][player->pos_x].entity.treasure = treasures;
                    }
                }
                break;

        case 2: if(inventory_add_object(player, treasures.objects[1])){
                    rm_obj.type = UNAVAILABLE;
                    treasures.objects[1] = rm_obj;
                    if(disappear_treasure(treasures)){
                        ground[player->pos_y][player->pos_x] = rm_cell;
                    }else{
                        ground[player->pos_y][player->pos_x].entity.treasure = treasures;
                    }
                }
                break;
        case 3: if(inventory_add_object(player, treasures.objects[2])){
                    rm_obj.type = UNAVAILABLE;
                    treasures.objects[2] = rm_obj;
                    ground[player->pos_y][player->pos_x].entity.treasure = treasures;
                    if(disappear_treasure(treasures)){
                        ground[player->pos_y][player->pos_x] = rm_cell;
                    }else{
                        ground[player->pos_y][player->pos_x].entity.treasure = treasures;
                    }
                }
                break;
        case 4: if(inventory_add_object(player, treasures.objects[3])){
                    rm_obj.type = UNAVAILABLE;
                    treasures.objects[3] = rm_obj;
                    ground[player->pos_y][player->pos_x].entity.treasure = treasures;
                    if(disappear_treasure(treasures)){
                        ground[player->pos_y][player->pos_x] = rm_cell;
                    }else{
                        ground[player->pos_y][player->pos_x].entity.treasure = treasures;
                    }
                }
                break;
                
        default:    break;
    }
}

void regeneration_effect(Player *player, int *reg_round){
    if((*reg_round) % 3 == 0){
        if(count_inventory_object_by_type(*player, REGENERATION) > 0){
            player_update_hp(player, 20);
            player_update_mp(player, 10);
        }
    }
    if((*reg_round) == 31){
        *reg_round += 0;
        inventory_remove_object(player, REGENERATION);
    }
    if(*reg_round == 0){
        if(count_inventory_object_by_type(*player, REGENERATION) > 0)
            *reg_round = 1;
    }
}

void precision_effect(Player *player, int *pre_round, int *prob){
    if((*pre_round) > 31){
        *pre_round = 0;
        *prob = 5;
        inventory_remove_object(player, PRECISION);
    }else{
        if((*pre_round) > 0)
            *prob = 15;
    }
    if((*pre_round) == 0){
        if(count_inventory_object_by_type(*player, PRECISION) > 0)
            *prob = 1;
    }
}

void learning_effect(Player *player, int *learn_round, int *bonus_exp){
    if((*learn_round) > 31){
        *learn_round = 0;
        *bonus_exp = 0;
        inventory_remove_object(player, LEARNING);
    }else{
        if((*learn_round) > 0)
            *bonus_exp = 15;
    }
    if((*learn_round) == 0){
        if(count_inventory_object_by_type(*player, LEARNING) > 0)
            *learn_round = 1;
    }

}