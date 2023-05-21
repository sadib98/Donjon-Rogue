#include <stdio.h>
#include <stdlib.h>
#include "../include/Graphic-Interface.h"

Coordinates** create_coordonnees(int width, int height, int zoom_size){
    Coordinates **coordinates;
    int i;
    coordinates = malloc(zoom_size * sizeof(Coordinates));
    for(i = 0; i < zoom_size; i++)
        coordinates[i] = malloc(zoom_size * sizeof(Coordinates));

    int line, column, size_x, size_y;
    int x1, y1, x2, y2;

    size_x = width  / zoom_size;
    size_y = height / zoom_size;

    x1 = 0;
    y1 = 0;
    x2 = x1 + size_x;
    y2 = y1 + size_y;

    for(line = 0; line < zoom_size; line++){
        for(column = 0; column < zoom_size; column++){
            coordinates[line][column].x1 = x1;
            coordinates[line][column].y1 = y1;
            
            coordinates[line][column].x2 = x2;
            coordinates[line][column].y2 = y2;
            x1 += size_x;
            x2 += size_x;
        }
        x1 = 0;
        x2 = x1 + size_x;
        y1 += size_y;
        y2 += size_y;
    }

    return coordinates;
}

void get_line_column_from_coordinates(int mouse_x, int mouse_y, int *line, int *column, int zoom_size, Coordinates **coordinates){
    int i, j;

    for(i = 0; i < zoom_size; i++){
        for(j = 0; j < zoom_size; j++){
            if(inclusion_test(coordinates[i][j].y1, coordinates[i][j].y2, mouse_y))
                *line = i;
            if(inclusion_test(coordinates[i][j].x1, coordinates[i][j].x2, mouse_x))
                *column = j;
        }
    }
}

Coordinates* create_treasures_coordinates(int x, int y){
    Coordinates *coordinates;
    coordinates = malloc(4 * sizeof(Coordinates));
    
    int x1, y1, size_x, gap;
    int i, j;
    

    x1 = x + 30;
    y1 = y + 60;
    size_x = 40;
    gap = size_x + 60;

    for(i = 0; i < 4; i++){
        coordinates[i].x1 = x1;
        coordinates[i].y1 = y1;
        coordinates[i].x2 = x1 + size_x;
        coordinates[i].y2 = y1 + size_x;
        x1 += gap;
    }
    return coordinates;
}

int get_treasures_option(Coordinates *coordinates, int mouse_x, int mouse_y){
    int i;

    for(i = 0; i < 4; i++){
        if(inclusion_test(coordinates[i].x1, coordinates[i].x2, mouse_x) && 
           inclusion_test(coordinates[i].y1, coordinates[i].y2, mouse_y)){
               return i+1;
           }
    }
}

int get_inventory_option(int mouse_x, int mouse_y){
    int x1, y1, size;

    x1 = 30;
    y1 = 420;
    size = 10;

    if(inclusion_test(y1, y1 + size, mouse_y)){
        if(inclusion_test(x1, x1 + size, mouse_x)){
            return 1;
        }
        if(inclusion_test(x1 + 45, x1 + 45  + size, mouse_x)){
            return 2;
        }
        if(inclusion_test(x1 + 45 * 2, x1 + 45 * 2  + size, mouse_x)){
            return 3; 
        }
        if(inclusion_test(x1 + 45 * 3, x1 + 45 * 3 + size, mouse_x)){
            return 4; 
        }
    }
    
    return 0;
}

static Cell get_cell_with_focus_area(int box_line, int box_column, Coordinates focus, Cell **ground){
    int from_ground_line, from_ground_column;

    from_ground_column = focus.x1 + box_column;
    from_ground_line = focus.y1 + box_line;

    return get_cell_on_ground(ground, from_ground_line, from_ground_column);
}

void display_objects(int width, int height, int box_size, Coordinates **coordinates, 
                   Coordinates focus, Cell **ground){
    int line, column;
    int size_x, size_y;
    Cell cell;
    MLV_Image *room, *wall, *door;
    MLV_Image *monster, *treasure;

    size_x = width  / box_size;
    size_y = height / box_size;

    monster = MLV_load_image( "images/Monster.jpg" );
    treasure = MLV_load_image( "images/Treasure.jpg" );
    wall = MLV_load_image( "images/Wall.jpg" );
    room = MLV_load_image( "images/Room.jpg" );
    door = MLV_load_image( "images/Door.jpg" );
    

    for(line = 0; line < box_size; line++){
        for(column = 0; column < box_size; column++){
            cell = get_cell_with_focus_area(line, column, focus, ground);
            switch (cell.type){

                case MONSTER: MLV_draw_image(monster, coordinates[line][column].x1, coordinates[line][column].y1);
                              MLV_draw_text(coordinates[line][column].x1, coordinates[line][column].y1, "%d", MLV_COLOR_RED, cell.entity.monster.hp);
                              break;
                
                case TREASURE: MLV_draw_image(treasure, coordinates[line][column].x1, coordinates[line][column].y1);
                               break;
                
                case WALL: MLV_draw_image(wall, coordinates[line][column].x1, coordinates[line][column].y1);
                           break;
                
                case ROOM: MLV_draw_image(room, coordinates[line][column].x1, coordinates[line][column].y1);
                           break;
                
                case STAIR_UP: MLV_draw_image(door, coordinates[line][column].x1, coordinates[line][column].y1);
                               break;
                
                default:     break;
            }
        }
    }

    MLV_free_image( monster );
    MLV_free_image( treasure );
    MLV_free_image( wall );
    MLV_free_image( room );
    MLV_free_image( door );
}


void get_focus_area_by_player(int lines, int columns, int zoom_size, Coordinates *focus, Player player){

    int player_x, player_y;

    player_x = player.pos_x;
    player_y = player.pos_y;

    zoom_size = zoom_size / 2;

    (*focus).x1 = player_x - (zoom_size - 1);
    (*focus).x2 = player_x + zoom_size + 1;
    (*focus).y1 = player_y - (zoom_size - 1);
    (*focus).y2 = player_y + zoom_size + 1;

    if(focus->x1 < 0){
        (*focus).x2 += focus->x1 * (-1);
        (*focus).x1 = 0;
    }
    if(focus->y1 < 0){
        (*focus).y2 += focus->y1 * (-1);
        (*focus).y1 = 0;
    }
    if(focus->x2 > columns){
        (*focus).x1 += focus->x2 - columns; 
        (*focus).x2 = columns;
    }
    if(focus->y2 > lines){
        (*focus).y1 += focus->y2 - lines;
        (*focus).y2 = lines;
    }

}

void move_focus_area(int lines, int columns, Player player, Coordinates *focus){

    if(player.pos_x < (focus->x1 + 2)){
        if((focus->x1 - 1) >= 0){
            (*focus).x1 -= 1;
            (*focus).x2 -= 1;
        }
    }
    
    if(player.pos_x > (focus->x2 - 3)){
        if((focus->x2 + 1) <= columns){
            (*focus).x2 += 1;
            (*focus).x1 += 1;
        }
    }
    
    if(player.pos_y < (focus->y1 + 2)){
        if((focus->y1 - 1) >= 0){
            (*focus).y1 -= 1;
            (*focus).y2 -= 1;
        }
            
    }
    
    if(player.pos_y > (focus->y2 - 3)){
        if((focus->y2 + 1) <= lines){
            (*focus).y2 += 1;
            (*focus).y1 += 1;
        }
    }
}

void move_player(int lines, int columns, Cell **ground, Player *player, MLV_Keyboard_button button, InfoType *info){
    Cell player_cell, check_cell;
    int player_x, player_y;
    int new_cell_x, new_cell_y;

    player_x = player->pos_x;
    player_y = player->pos_y;


    switch (button){

        case MLV_KEYBOARD_UP : new_cell_y = player_y - 1;
                                check_cell = get_cell_on_ground(ground, new_cell_y, player_x);
                               if(new_cell_y >= 0 && (check_cell.type == ROOM || check_cell.type == STAIR_UP || check_cell.type == TREASURE)){
                                   if(count_neighbors_by_type(lines, columns, ground, check_cell, MONSTER, 1) > 0){
                                        if(*info != ATTACK || *info != MAGICAL_ATK)
                                            *info = ATTACK;
                                   }else{
                                       *info = NONE;
                                   }
                                   (*player).pos_y = new_cell_y;
                               }
                               break;

        case MLV_KEYBOARD_DOWN : new_cell_y = player_y + 1;
                                check_cell = get_cell_on_ground(ground, new_cell_y, player_x);
                                 if(new_cell_y <= lines && (check_cell.type == ROOM || check_cell.type == STAIR_UP || check_cell.type == TREASURE)){
                                     if(count_neighbors_by_type(lines, columns, ground, check_cell, MONSTER, 1) > 0){
                                        if(*info != ATTACK || *info != MAGICAL_ATK)
                                            *info = ATTACK;
                                     }else{
                                            *info = NONE;
                                     }
                                     (*player).pos_y = new_cell_y;
                                 }
                                 break;
        
        case MLV_KEYBOARD_LEFT : new_cell_x = player_x - 1;
                                check_cell = get_cell_on_ground(ground, player_y, new_cell_x);
                                 if(new_cell_x >= 0 && (check_cell.type == ROOM || check_cell.type == STAIR_UP || check_cell.type == TREASURE)){
                                    if(count_neighbors_by_type(lines, columns, ground, check_cell, MONSTER, 1) > 0){
                                        if(*info != ATTACK || *info != MAGICAL_ATK)
                                            *info = ATTACK;
                                    }else{
                                       *info = NONE;
                                    }
                                    (*player).pos_x = new_cell_x;
                                 }
                                 break;
        
        case MLV_KEYBOARD_RIGHT : new_cell_x = player_x + 1;
                                  check_cell = get_cell_on_ground(ground, player_y, new_cell_x);
                                  if((new_cell_x <= columns) && (check_cell.type == ROOM || check_cell.type == STAIR_UP || check_cell.type == TREASURE)){
                                    if(count_neighbors_by_type(lines, columns, ground, check_cell, MONSTER, 1) > 0){
                                        if(*info != ATTACK || *info != MAGICAL_ATK)
                                            *info = ATTACK;
                                    }else{
                                       *info = NONE;
                                    }
                                    (*player).pos_x = new_cell_x;
                                  }
                                  break;

        default                 : break;
    }
}

void display_player_details(Player player){
    MLV_Image *player_img;
    int x1, y1;
    x1 = 64;
    y1 = 385;

    player_img = MLV_load_image("images/Player.png");
    MLV_draw_filled_rectangle(0, y1 - 17, 64, 48, MLV_COLOR_GRAY10);
    MLV_draw_image(player_img, 0, y1 - 17);

    MLV_draw_adapted_text_box(x1, y1, "Hp:%d, Mp:%d, Atk:%d, Int:%d, Def:%d Exp:%d, Lv:%d", 8, 
                              MLV_COLOR_GRAY10, MLV_COLOR_WHITE, MLV_COLOR_GRAY10, MLV_TEXT_LEFT,
                              player.hp, player.mp, player.atk, player.intel, player.def, player.exp, player.lv);
    MLV_free_image(player_img);
}

void display_player_inventory(Player player){
    int x1, y1;
    MLV_Image *potion, *armor, *weapon, *wand;
    x1 = 0;
    y1 = 420;
    potion = MLV_load_image("images/Potion.png");
    armor = MLV_load_image("images/Armor.png");
    weapon = MLV_load_image("images/Weapon.png");
    wand = MLV_load_image("images/Wand.png");

    MLV_draw_filled_rectangle(x1, y1, 40, 40, MLV_COLOR_WHITE);
    MLV_draw_image(potion, x1, y1);
    MLV_draw_text(x1, y1+25, "%d", MLV_COLOR_BLUE3, count_inventory_potions(player));
    MLV_draw_text(x1 + 30, y1, "X", MLV_COLOR_RED1);

    MLV_draw_filled_rectangle(x1 + 45, y1, 40, 40, MLV_COLOR_WHITE);
    MLV_draw_image(armor, x1 + 45, y1);
    MLV_draw_text(x1 + 45, y1+25, "%d", MLV_COLOR_BLUE3, count_inventory_object_by_type(player, ARMOR));
    MLV_draw_text(x1 + 75, y1, "X", MLV_COLOR_RED1);

    MLV_draw_filled_rectangle(x1 + 45 * 2, y1, 40, 40, MLV_COLOR_WHITE);
    MLV_draw_image(weapon, x1 + 45 * 2, y1);
    MLV_draw_text(x1 + 45 * 2, y1+25, "%d", MLV_COLOR_BLUE3, count_inventory_object_by_type(player, WEAPON));
    MLV_draw_text(x1 + 45 * 2 + 30, y1, "X", MLV_COLOR_RED1);

    MLV_draw_filled_rectangle(x1 + 45 * 3, y1, 40, 40, MLV_COLOR_WHITE);
    MLV_draw_image(wand, x1 + 45 * 3, y1);
    MLV_draw_text(x1 + 45 * 3, y1+25, "%d", MLV_COLOR_BLUE3, count_inventory_object_by_type(player, WAND));
    MLV_draw_text(x1 + 45 * 3 + 30, y1, "X", MLV_COLOR_RED1);

    MLV_free_image(potion);
    MLV_free_image(armor);
    MLV_free_image(weapon);
    MLV_free_image(wand);
}

void display_player(int zoom_size, Coordinates **coordinates, Player player, Coordinates focus){
    int i, j;
    int detect_x, detect_y;
    MLV_Image *player_img;

    player_img = MLV_load_image("images/Player.png");

    for(i = 0; i < zoom_size; i++){
        for(j = 0; j < zoom_size; j++){
            detect_x = j + focus.x1;
            detect_y = i + focus.y1;
            if(detect_x == player.pos_x && detect_y == player.pos_y){
                MLV_draw_image(player_img, coordinates[i][j].x1, coordinates[i][j].y1);
                MLV_draw_text(coordinates[i][j].x1-5, coordinates[i][j].y1-10, "%d", MLV_COLOR_RED1, player.hp);
                break;
            }
        }
    }
    display_player_details(player);
    display_player_inventory(player);

    MLV_free_image(player_img);
}

void can_treasure_explore(Cell **ground, Player player, InfoType *info){
    if(get_cell_on_ground(ground, player.pos_y, player.pos_x).type == TREASURE){
        *info = TREASURE_EXPLORE;
    }
}

void display_treasure_objects(Object_type type, int x, int y){
    MLV_Image *potion, *armor, *weapon, *wand;

    switch(type){
        case CARE:
        case MAGIC:
        case REGENERATION:
        case PRECISION:
        case LEARNING:  potion = MLV_load_image("images/Potion.png");
                        MLV_draw_image(potion, x, y);
                        MLV_free_image(potion);
                        break;
        
        case ARMOR: armor = MLV_load_image("images/Armor.png");
                    MLV_draw_image(armor, x, y);
                    MLV_free_image(armor);
                    break;
        
        case WEAPON: weapon = MLV_load_image("images/Weapon.png");
                     MLV_draw_image(weapon, x, y);
                     MLV_free_image(weapon);
                     break;
        
        case WAND:  wand = MLV_load_image("images/Wand.png");
                    MLV_draw_image(wand, x, y);
                    MLV_free_image(wand);
                    break;
        
        default:    break;
    }
}

void display_treasure_explore(Cell **ground, Coordinates *coordinates, Player player, InfoType info){
    Cell treasure_cell;
    int x, y, width, height;
    int object_x, object_y;
    int i;
    int radius;

    x = 125;
    y = 100;
    width = 400;
    height = 130;
    if(info == TREASURE_EXPLORE){
        MLV_draw_filled_rectangle(x, y, width, height, MLV_COLOR_WHITE);
        MLV_draw_text(x+10, y+10, "TREASURES", MLV_COLOR_BLUE4);

        treasure_cell = ground[player.pos_y][player.pos_x];
        for(i = 0; i < 4; i++){
            display_treasure_objects(treasure_cell.entity.treasure.objects[i].type, coordinates[i].x1, coordinates[i].y1);
        }
    }
    
}

void change_attack_type(Player player, InfoType *info, MLV_Keyboard_button button){
    if(button == MLV_KEYBOARD_c){
        if((*info) == ATTACK && player.mp >= 20)
            *info = MAGICAL_ATK;
        else if((*info) == MAGICAL_ATK)
            *info = ATTACK;
    }
}

void display_informations(InfoType info, Cell **ground, Player player){
    switch(info){
        case ATTACK: MLV_draw_adapted_text_box(
                        250, 1,
                        "Attack type: NORMAL\nPress on C to change.",
                        8,
                        MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                        MLV_TEXT_CENTER
                    );
                    break;

        case MAGICAL_ATK: MLV_draw_adapted_text_box(
                        250, 1,
                        "Attack type: Magical Attack\nPress on C to change.",
                        8,
                        MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_WHITE,
                        MLV_TEXT_CENTER
                    );
                    break;

        default: break;
    }
}


int display_menu(int width, int height){
    MLV_Image *background, *newgame, *resume;
    int mouse_x, mouse_y;
    int x, y;
    int seed, found;

    x = 230;
    y = 200;

    background = MLV_load_image("images/Menu-background.jpg");
    newgame = MLV_load_image("images/Newgame.png");
    resume = MLV_load_image("images/Resume.png");

    found = load_game(&seed);
    /* Background */
    MLV_draw_image(background, 0, 0);

    /* Option 1 */
    MLV_draw_image(newgame, x, y);

    /* Option 2 */
    if(found){
        MLV_draw_image(resume, x, y + 70);
    }

    while(1){
        MLV_actualise_window();
        MLV_wait_mouse(&mouse_x, &mouse_y);
        if(inclusion_test(x, x + 200, mouse_x)){
            if(inclusion_test(y, y + 50, mouse_y)){
                return time(0);
            }
            if(found){
                if(inclusion_test(y + 70, y + 120, mouse_y)){
                    return seed;
                }
            }
        }
    }

    MLV_free_image(background);
}