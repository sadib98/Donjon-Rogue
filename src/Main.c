#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "../include/Player.h"
#include "../include/Monster.h"
#include "../include/Treasure.h"
#include "../include/Attack.h"
#include "../include/Ground.h"
#include "../include/Graphic-Interface.h"
#include "../include/Create-objects.h"
#include "../include/Put-objects.h"
#include "../include/Change-state.h"

int main(){
    Cell **ground;
    Coordinates **coordinates;
    Coordinates *treasure_objects_coordinates;
    Coordinates focus;
    Player player;
    MLV_Event event;
    MLV_Keyboard_button key_pressed;
    MLV_Button_state state;

    int probability, bonus_exp;
    probability = 5;
    bonus_exp = 0;

    int reg_round, pre_round, learn_round;
    reg_round = 0;
    pre_round = 0;
    learn_round = 0;

    int mouse_x, mouse_y;
    int stage, i , j;
    
    InfoType info;
    info = NONE;
    
    int treasure_popup_x, treasure_popup_y;

    treasure_popup_x = 125;
    treasure_popup_y = 100;

    int width, height, zoom_size;
    int lines, columns;

    width = 640;
    height = 480;
    zoom_size = 10;

    lines = 43;
    columns = 63;

    int seed;

    MLV_execute_at_exit(save_game, &seed);
    MLV_create_window( "Donjon Rogue", "donjon", width, height);

    seed = display_menu(width, height);
    
    srand(seed);

    /* Element creation */
    coordinates = create_coordonnees(width, height, zoom_size);
    treasure_objects_coordinates = create_treasures_coordinates(treasure_popup_x, treasure_popup_y);
    ground = create_ground(lines, columns);
    player = create_player();
    
    /* Placing elements */
    put_treasures(lines, columns, ground, 10, player.lv);
    put_guards(lines, columns, ground);
    put_player(lines, columns, ground, &player);
    
    /* Get camera vision zone */
    get_focus_area_by_player(lines, columns, zoom_size, &focus, player);

    while(1){
        MLV_clear_window(MLV_COLOR_BLACK);

        display_objects(width, height, zoom_size, coordinates, focus, ground);
        display_player(zoom_size, coordinates, player, focus);
        display_informations(info, ground, player);
        display_treasure_explore(ground, treasure_objects_coordinates, player, info);

        MLV_actualise_window();

        event = MLV_get_event(&key_pressed, NULL, NULL, NULL, NULL, &mouse_x, &mouse_y, NULL, &state);
        
        if(event == MLV_KEY && state == MLV_PRESSED){
            move_player(lines, columns, ground, &player, key_pressed, &info);
            move_focus_area(lines, columns, player, &focus);
            can_treasure_explore(ground, player, &info);
            change_attack_type(player, &info, key_pressed);
        }else if(event == MLV_MOUSE_BUTTON && state == MLV_PRESSED){
            if(info == ATTACK || info == MAGICAL_ATK){
                if(player_attack(&player, mouse_x, mouse_y, zoom_size, coordinates, focus, lines, columns, ground, info, probability, bonus_exp)){
                    if(reg_round != 0)
                        reg_round += 1;
                    if(pre_round != 0)
                        pre_round += 1;
                    if(learn_round != 0)
                        learn_round += 1;
                }            
            }        
            if(info == TREASURE_EXPLORE){
                inventory_add_by_option(ground, &player, 
                    get_treasures_option(treasure_objects_coordinates, mouse_x, mouse_y)
                );
            }
            
            inventory_remove_by_option(&player, 
                get_inventory_option(mouse_x, mouse_y)
            );
        }
        /* Auto checking phase */
        regeneration_effect(&player, &reg_round);    
        precision_effect(&player, &pre_round, &probability);
        learning_effect(&player, &learn_round, &bonus_exp);
        player_update_lv(&player);

        if(is_dead(player.hp)){
            printf("Game Over !\n");
            printf("Player exp: %d , level: %d!\n", player.exp, player.lv);
            break;
        }

        MLV_actualise_window();
    }
    
    MLV_actualise_window();
    MLV_free_window();
    
    
    return 1;
}