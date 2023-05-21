#ifndef __PLAYER__
#define __PLAYER__
#include "Treasure.h"
#include "Ground.h"

typedef struct player{
    int hp;
    int mp;
    int atk;
    int intel;
    int def;
    int exp;
    int lv;
    Treasure inventory;
    int pos_x;
    int pos_y;
} Player;

/* Function that initializes the attributes of the player */
void player_init(Player *player);

/* Function that updates the player's hp points*/
void player_update_hp(Player *player, int points);

/* Function that updates the player's mp points*/
void player_update_mp(Player *player, int points);

/* Function that updates the player's atk points*/
void player_update_atk(Player *player, int atk_shot);

/* that updates the player's intelligence points*/
void player_update_intel(Player *player, int intel_point);

/* Function updates player's defenses. */
void player_update_def(Player *player, int def_point);

/* Function updates player experiences. */
void player_update_exp(Player *player, int new_exp);

/* Function updates player's level and returns 1 or returns 0. */
int player_update_lv(Player *player);

/* Funtion updates points by player's chioce when level updates */
void level_upgrade_points(Player *player, int option);

int count_inventory_object_by_type(Player player, Object_type type);

int count_inventory_potions(Player player);

void inventory_remove_by_option(Player *player, int option);

void inventory_add_by_option(Cell **ground, Player *player, int option);

void regeneration_effect(Player *player, int *reg_round);

void precision_effect(Player *player, int *pre_round, int *prob);

void learning_effect(Player *player, int *learn_round, int *bonus_exp);
#endif