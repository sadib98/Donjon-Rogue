#include <stdio.h>
#include <stdlib.h>
#include "../include/Create-objects.h"

Player create_player(){
    Player player;
    player_init(&player);
    return player;
}

Cell create_monster(int line, int column){
    Cell cell;
    Entity entity;
    Monster monster;

    int hp, atk;
    hp = random_min_max(20, 40);
    atk = random_min_max(3, 8);

    monster_init(&monster, hp, atk);
    entity.monster = monster;
    cell.type = MONSTER;
    cell.entity = entity;
    cell.line = line;
    cell.column = column;

    return cell;
}

Cell create_treasure(int line, int column, int level){
    Cell cell;
    Entity entity;
    Treasure treasure;

    treasure.total = 4;
    init_treasure(&treasure, level);
    entity.treasure = treasure;
    
    cell.type = TREASURE;
    cell.entity = entity;
    cell.line = line;
    cell.column = column;

    return cell;
}

Cell create_wall(int line, int column){
    Cell cell;
    cell.type = WALL;
    cell.line = line;
    cell.column = column;
    return cell;
}

Cell create_room(){
    Cell cell;
    cell.type = ROOM;
    return cell;
}

Cell create_stair_up(int line, int column){
    Cell cell;
    cell.type = STAIR_UP;
    cell.line = line; 
    cell.column = column;
    return cell;
}

Cell create_stair_down(){
    Cell cell;
    cell.type = STAIR_DOWN;
    return cell;
}

Cell** create_ground(int lines, int columns){
    Cell **ground;
    int i;

    ground = malloc(lines * sizeof(Cell));

    for(i = 0; i < lines; i++)
        ground[i] = malloc(columns * sizeof(Cell));

    put_walls(lines, columns, ground);
    put_stair_up(lines, columns, ground);
    generate_labyrinth(lines, columns, ground);

    return ground;
}