#ifndef __LIST_MANAGER__
#define __LIST_MANAGER__
    #include "Ground.h"

    void remove_from_list(Cell list[], int *length, int toremove);
    void clear_list(Cell list[], int *length);
    int exist_in_list(Cell list[], int length, Cell toCheck);
    void add_to_list(Cell list[], int *length, Cell toadd);
    void addlist_to_list(Cell from_list[], Cell to_list[], int *from_length, int *to_length);
#endif