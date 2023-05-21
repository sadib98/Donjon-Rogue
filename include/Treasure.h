#ifndef __TREASURE__
#define __TREASURE__
#include "Extra-functions.h"

/*Definition of the type Potion*/
typedef enum{
    UNAVAILABLE, CARE, MAGIC, REGENERATION, PRECISION, LEARNING,
    ARMOR, WEAPON, WAND
} Object_type;

typedef struct object{
    Object_type type;
    int value;
} Object;

/*Definition of the type Treasure*/
typedef struct treasure{
    Object *objects;
    int total;
} Treasure;

/* Function that initializes treasure */
void init_treasure(Treasure *T, int level);
/* Grants a bonus to the player according to the potion taken*/
/* void postion_effects(Player *player, TypePotion potion); */

/* Grants a bonus to the player according the arm, the weapon and the wand find in the treasure*/
/* void equipment_effects(Player *player, Treasure T); */


#endif