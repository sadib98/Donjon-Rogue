#ifndef __ATTACK__
#define __ATTACK__
#include "Extra-functions.h"
#include "Player.h"
#include "Monster.h"
#include "Ground.h"
#include "Ground-generator.h"
#include "Graphic-Interface.h"

/* Function returns damage occured by attribute given */
int damage(int attribute);

/* Funtion returns 1 if the 5% probability of a critical attack has occurred or returns 0. */
int critical_hit(int probability);

/* Function returns an integer of damage after a magical hit. */
int magical_hit(Player *player);

/* Function returns 1 if hp == 0 or returns 0. */
int is_dead(int hp);

int player_attack(Player *player, int mouse_x, int mouse_y, int zoom_size, Coordinates **coordinates, Coordinates focus, int lines, int columns, Cell **ground, InfoType info, int probability, int bonus_exp);
#endif