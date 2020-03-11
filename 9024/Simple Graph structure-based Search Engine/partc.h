//
// Created by 王晓雨 on 15/1/20.
//
# include <stdbool.h>
#include <string.h>
#ifndef ASSIGNMENT_PARTC_H
#define ASSIGNMENT_PARTC_H

#endif //ASSIGNMENT_PARTC_H
#define MAXWORD 20

typedef char STR[MAXWORD];


typedef struct nodec {
    char data[MAXWORD];
    struct nodec *next;
} Nodec;

typedef struct rank {
    char page[MAXWORD];
    float weight;
    struct rank *next;
} rank;

typedef struct sample{
    char page[MAXWORD];
    int count;
    float weight;
    struct sample *next;
} Sample;

bool indexwordc(char **a, char*b);
Nodec *Makenodec(char *x);                   // make node(valuing x) at the beginning
void insertEndc(Nodec *list, char *d);      // insert a new element at the end
Nodec *insertRc(Nodec *head, Nodec *node);  //insert a node into an ordered list (recursive)
void showlistc(Nodec *list);


rank *Makerank(char *x,float w);
rank *append(rank *list, rank *new);
Sample *Makesample(char *x);
Sample *addsample(Sample *list, char *data);
bool ifexistsample(Sample *list, char *data);
void showresult(Sample *list);
Sample *addweight(Sample *list, rank *s);
Sample *sortcount(Sample *list);
Sample *sortweight(Sample *list);
int lengthSample(Sample *list);

void freepointc(Nodec *list);
void freerankc(rank *list);
void freesample(Sample *list);