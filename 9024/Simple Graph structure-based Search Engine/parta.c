//
// Created by 王晓雨 on 17/1/20.
//
# include "parta.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
#include <string.h>

Nodea *Makenodea(char *x) {
    Nodea *new = malloc(sizeof(Nodea));
    assert(new != NULL);
    strcpy(new->data, x);
    new->next = NULL;               //initialise link to next node
    return new;                     // return pointer to new node
}

void insertEnda(Nodea *list, char *d) {

    while(list->next != NULL){
        list = list->next;
    }
    list->next = Makenodea(d);                    // create new element data

}

void showlista(Nodea *list) {
    Nodea *p;
    //printf("the list is: \n");
    for(p = list; p!= NULL; p = p ->next){
        printf("%s\n",p->data);
    }

}

int lengthlista(Nodea *list) {
    Nodea *p;
    int x = 1;
    for(p = list; p!= NULL; p = p ->next){
        x++;
    }
    x--;
    return x;
}

int indexnodea(Nodea *list, char *n) {
    Nodea *p;
    int x=0;
    for(p = list; p!= NULL; p = p ->next){
        if (strcmp(p->data,n)==0){
            return x;
        }else{
            x++;
        }
    }
    return 0;
}


