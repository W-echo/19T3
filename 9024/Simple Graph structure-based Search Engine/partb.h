//
// Created by 王晓雨 on 21/1/20.
//
# include <ctype.h>
# include <stdbool.h>
#ifndef ASSIGNMENT_PARTB_H
#define ASSIGNMENT_PARTB_H

#endif //ASSIGNMENT_PARTB_H
#define MAXSTRING 1000
#define MAXPAGE 30
#define MAXWORD 20

typedef struct link {
    int url;
    struct link *next;
} Link;

typedef struct nodeb {
    char data[MAXWORD];   //words
    struct nodeb *next;
    Link *l;     // page
} Nodeb;



Nodeb *Makenodeb(char *x);                   // make node(valuing x) at the beginning
void insertEndb(Nodeb *list, char *d);      // insert a new element at the end
void showlistb(Nodeb *list);
int lengthlistb(Nodeb *list);                 // return the length of linked list
int indexnodeb(Nodeb *list,char *n);                     // return the place of the node
bool ifnodeexistb(Nodeb *list, Nodeb *n);
Nodeb *insertRb(Nodeb *head, Nodeb *node);
Nodeb *newinsertRb(Nodeb *head, Nodeb *node);
void clearlink(Nodeb *phead);
Nodeb *readSection2(char *urlname);
Nodeb *addlinkedlistb(Nodeb *list, Nodeb *addlist);
Nodeb *addpagelinkb(Nodeb *list, Nodeb *new);

Link *insertListOrder(Link *t, int x);
Link *Makelink(int x);
void showpage(Link *page);

void freepointb(Nodeb *list);
void freelinkb(Link *list);