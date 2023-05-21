#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/List-manager.h"

void remove_from_list(Cell list[], int *length, int toremove){
    int i;
    if(*length != 0){
        for(i = toremove; i < *length - 1; i++){
            list[i] = list[i + 1];
        }
        *length -= 1;
    }
}

void clear_list(Cell list[], int *length){
    memset(list, 0, (*length) * sizeof(Cell));
    *length = 0;
}

int exist_in_list(Cell list[], int length, Cell toCheck){
    int i;
    for(i = 0; i < length; i++){
        if((list[i].line == toCheck.line) && (list[i].column == toCheck.column))
            return 1;
    }
    return 0;
}

void add_to_list(Cell list[], int *length, Cell toadd){
    if(exist_in_list(list, *length, toadd) == 0){
        list[*length] = toadd;
        *length += 1;
    }
}

void addlist_to_list(Cell from_list[], Cell to_list[], int *from_length, int *to_length){
    int i;
    for(i = 0; i < *from_length; i++){
        add_to_list(to_list, to_length, from_list[i]);
    }
    
    *from_length = 0;
}
