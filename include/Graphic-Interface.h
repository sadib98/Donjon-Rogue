#ifndef __GRAPHIC_INTERFACE__
#define __GRAPHIC_INTERFACE__
    #include <MLV/MLV_all.h>
    #include <time.h>
    #include "Extra-functions.h"
    #include "Player.h"
    #include "Ground.h"
    #include "Ground-generator.h"

    typedef struct coordinates {
        int x1;
        int y1;
        int x2;
        int y2;
    } Coordinates;

    typedef enum {
        NONE, ATTACK, MAGICAL_ATK, TREASURE_EXPLORE
    } InfoType; 

    Coordinates** create_coordonnees(int width, int height, int box_size);
    
    void get_line_column_from_coordinates(int mouse_x, int mouse_y, int *line, int *column, int zoom_size, Coordinates **coordinates);

    Coordinates* create_treasures_coordinates(int x, int y);

    int get_treasures_option(Coordinates *coordinates, int mouse_x, int mouse_y);

    int get_inventory_option(int mouse_x, int mouse_y);

    void display_objects(int width, int height, int box_size, Coordinates **coordinates, 
                   Coordinates focus, Cell **ground);
    
    void move_player(int lines, int columns, Cell **ground, Player *player, MLV_Keyboard_button button, InfoType *info);

    void get_focus_area_by_player(int lines, int columns, int zoom_size, Coordinates *focus, Player player);

    void move_focus_area(int lines, int columns, Player player, Coordinates *focus);

    void display_player(int zoom_size, Coordinates **coordinates, Player player, Coordinates focus);
    
    void can_treasure_explore(Cell **ground, Player player, InfoType *info);

    void display_treasure_explore(Cell **ground, Coordinates *coordinates, Player player, InfoType info);

    void change_attack_type(Player player, InfoType *info, MLV_Keyboard_button button);

    void display_informations(InfoType info, Cell **ground, Player player);

    int display_menu(int width, int height);

#endif