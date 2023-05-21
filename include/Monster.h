#ifndef __MONSTER__
#define __MONSTER__

/* Structure that defines monster according their hp and atk*/
typedef struct monster{
    int hp;
    int atk;
} Monster;

/* Function that initializes monster atk and hp randomly*/
void monster_init(Monster *monster, int hp, int atk);

/* Function that updates monster's hp*/
void monster_update_hp(Monster *monster, int points);

/* Function that updates monster's atk*/
void monster_update_atk(Monster *monster, int points);

#endif