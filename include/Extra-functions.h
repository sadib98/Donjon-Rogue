#ifndef __EXTRA_FUNCTIONS__
#define __EXTRA_FUNCTIONS__

    int random_min_max(int min, int max);

    int manhattan_distance(int i1, int j1, int i2, int j2);
    
    int inclusion_test(int a, int b, int toTest);

    void save_game(void *data);

    int load_game(int *seed);
#endif