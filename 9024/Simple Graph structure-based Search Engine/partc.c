//
// Created by 王晓雨 on 15/1/20.
//
#include "partc.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
#include <string.h>

bool indexwordc(char **a, char*b) {
    int i=0;
    char *pdata;
    while(a[i]!=NULL){
        pdata = a[i];
        i++;
        if(strcmp(pdata, b)==0) {
            return true;
        }
    }
    return false;
}

Nodec *Makenodec(char *x) {
    Nodec *new = malloc(sizeof(Nodec));
    assert(new != NULL);
    strcpy(new->data, x);
    new->next = NULL;               //initialise link to next node
    return new;                     // return pointer to new node
}


rank *Makerank(char *x, float w){
//    printf("enter makerank");
//    printf("%s  %f",x, w);
    rank *new = malloc(sizeof(rank));
    assert(new != NULL);

    strcpy(new->page, x);
    new->weight = w;
    new->next = NULL;
//    printf("%s %.7f", new->page, new->weight);
    return new;
}

void insertEndc(Nodec *list, char *d) {

    while(list->next != NULL){
        list++;
    }
    list->next = Makenodec(d);                    // create new element data

}


rank *append(rank *list, rank *new) {
//    printf("start app\n");
    rank* curr = list;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = new;
    return list;
}


//insert a node into an ordered list (recursive) ,return head pointer
Nodec *insertRc(Nodec *head, Nodec *node) {
    if (head == NULL || head->data >= node->data){
        node->next = head;
        return node;
    }
    head->next = insertRc(head->next,node);
    return head;
}

void showlistc(Nodec *list) {
    Nodec *p;
    printf("the list is: \n");
    for(p = list; p!= NULL; p = p ->next){
        printf("%s\n", p->data);
    }
}

Sample *Makesample(char *x){
    Sample *new = malloc(sizeof(Sample));
    assert(new!=NULL);
    strcpy(new->page, x);
    new->count = 1;
    new->weight = 0;
    new->next = NULL;               //initialise link to next node
    return new;
}

Sample *addsample(Sample *list, char *data){
    Sample *curr = list;
    Sample *new = Makesample(data);
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = new;
    return list;
}

bool ifexistsample(Sample *list, char *data){
    Sample *curr;
    for (curr = list; curr!=NULL; curr=curr->next){
        if (strcmp(curr->page, data)==0){
            curr->count++;
            return true;
        }
    }
    return false;
}

void showresult(Sample *list){
    Sample *curr = list;
    printf("the result is:\n");
    while(curr!=NULL){
        printf("%s: %d  %.7f \n", curr->page, curr->count, curr->weight);
        curr= curr->next;
    }
}

Sample *addweight(Sample *list, rank *s){
    Sample *curr;
    for(curr=list; curr!=NULL; curr=curr->next){
        if(strcmp(curr->page,s->page)==0){
            curr->weight = s->weight;
//            printf("%s %.7f\n", curr->page, curr->weight);
            return list;
        }
    }
    return list;
}

int lengthSample(Sample *list){
    int i = 0;
    while(list!= NULL){
        list = list->next;
        i++;
    }
    return i;
}
int countflag(Sample *list, int count){
    int len=0;
    while(list!=NULL){
        if (list->count == count){
            len++;
        }
        list = list->next;
    }
    return len;
}

Sample *sortcount(Sample *list){
    int len = lengthSample(list);
//    printf("%d\n",len);
    Sample *y;
    char page[MAXWORD];
    float weight;
    int count;
    int i,j;
    for(i=0; i<len-1; i++){
        j = 0;
        for(y = list; j<len-1-i;y = y->next){
            if (y->count<y->next->count){
                strcpy(page,y->page); weight = y->weight; count = y->count;
                strcpy(y->page,y->next->page); y->weight = y->next->weight; y->count = y->next->count;
                strcpy(y->next->page,page); y->next->weight = weight; y->next->count = count;
            }
            j++;
        }

    }
    return list;
}

Sample *sortweight(Sample *list){   // sort weight in the same count

    int flag;       // record the number count
    Sample *x, *y;
    // store data as temp
    char page[MAXWORD];
    float weight;
    int count;

    int i,j;
    x = list;
    Sample *start=list;
    flag = list->count;
    int len = countflag(list,flag);
//    printf("%d\n",len);
    while (start!=NULL){
        for(i=0; i<len-1; i++){
            x = x->next;
            j = 0;
            for(y=start; j<len-1-i; y = y->next){
                if (y->weight<y->next->weight){
                    strcpy(page,y->page); weight = y->weight; count = y->count;
                    strcpy(y->page,y->next->page); y->weight = y->next->weight; y->count = y->next->count;
                    strcpy(y->next->page,page); y->next->weight = weight; y->next->count = count;
                }
                j++;
            }
        }
        x = x->next;
        if(x==NULL){
            break;
        }else{
            start = x;
//            printf("%s\n",start->page);
            len = countflag(start,start->count);
//            printf("%d\n",len);
        }
    }
    return list;
}


void freepointc(Nodec *list){
    if (list != NULL) {
        freepointc(list->next);
        free(list);
    }
}
void freerankc(rank *list){
    if (list != NULL) {
        freerankc(list->next);
        free(list);
    }
}
void freesample(Sample *list){
    if (list != NULL) {
        freesample(list->next);
        free(list);
    }
}