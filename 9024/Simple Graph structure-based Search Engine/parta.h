//
// Created by 王晓雨 on 17/1/20.
//

#ifndef ASSIGNMENT_PARTA_H
#define ASSIGNMENT_PARTA_H

#endif //ASSIGNMENT_PARTA_H
#define MAXPAGE 30
#define MAXWORD 20

typedef struct nodea {
    char data[MAXWORD];
    struct nodea *next;
} Nodea;


typedef struct weightresult{
    char data[MAXWORD];
    int outdeg;
    float weight;
    struct weightresult *next;
}Wresult;

Nodea *Makenodea(char *x);                   // make node(valuing x) at the beginning
void insertEnda(Nodea *list, char *d);      // insert a new element at the end
void showlista(Nodea *list);
int lengthlista(Nodea *list);                 // return the length of linked list
int indexnodea(Nodea *list,char *n);                     // return the place of the node

Wresult *Makewresult(char *x, int y, float z);
void insertWresult(Wresult *list, Wresult *new);
void showwresult(Wresult *x);
Wresult *sortwei(Wresult *list);
int lengtha(Wresult *list);