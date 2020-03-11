//
// Created by 王晓雨 on 21/1/20.
//

# include "partb.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
#include <string.h>


Link *Makelink(int x) {
    Link *new = malloc(sizeof(Link));
    assert(new != NULL);
    new->url = x;
    new->next = NULL;               //initialise link to next node
    return new;                     // return pointer to new node
}


Nodeb *Makenodeb(char *x) {
    Nodeb *new = malloc(sizeof(Nodeb));
    assert(new != NULL);
    strcpy(new->data, x);
    new->l=Makelink(0);
    new->next = NULL;               //initialise link to next node
    //printf("success make node\n");
    return new;                     // return pointer to new node
}

void showlistb(Nodeb *list) {
    Nodeb *p;
    //printf("the list is: \n");
    for(p = list; p!= NULL; p = p ->next){
        printf("%s\n",p->data);
    }

}

int lengthlistb(Nodeb *list) {
    Nodeb *p;
    int x = 1;
    for(p = list; p!= NULL; p = p ->next){
        x++;
    }
    x--;
    return x;
}

bool ifnodeexistb(Nodeb *list, Nodeb *n) {
    Nodeb *p;
    for(p = list; p!= NULL; p = p ->next){
        if (strcmp(p->data,n->data)==0){
            //printf("T");
            return true;
        }
    }
//    printf("F");
    return false;

}


void insertEndb(Nodeb *list, char *d) {

    while(list->next != NULL){
        list= list->next;
    }
    list->next = Makenodeb(d);                    // create new element data
    // printf("add node: %s\n",list->next->data);
}

Link *insertListOrder(Link *t, int x){       // insert page link into linked list
    Link *p ;
    Link *q=Makelink(x);
    for (p = t; p!= NULL; p=p->next){
        if (p->next != NULL) {
            if (p->url<x && p->next->url>x){
                q->next = p->next;
                p->next = q;
                return t;
            }
        }else{     // p->next == null
            p->next = q;
            return t;
        }
    }
}
int indexnodeb(Nodeb *list, char *n) {
    Nodeb *p;
    int x=0;
    for(p = list; p!= NULL; p = p ->next){
        if (strcmp(p->data,n)==0){
            return x;
        }else{
            x++;
        }
    }
}

//insert a node into an ordered list (recursive) ,return head pointer
Nodeb *insertRb(Nodeb *head, Nodeb *node) {
    if (head == NULL || (strcmp(head->data, node->data)>0)){
        node->next = head;
        //head->next = node;
        return node;
    }
    head->next = insertRb(head->next,node);
    return head;
}

Nodeb *newinsertRb(Nodeb *head, Nodeb *node) {
    Nodeb *p ;
    if ((strcmp(head->data, node->data)>0)){
        node->next = head;
        return node;
    }
    for(p = head; p->next!= NULL; p =p->next){
        if ((strcmp(p->data, node->data)<0)&&(strcmp(p->next->data, node->data)>0)){
            node->next = p->next;
            p->next = node;
            return head;
        }
    }
    if (p->next == NULL){
        p->next = node;
        return head;
    }

}



void clearlink(Nodeb *phead)
{
    Nodeb *q=NULL;
    while(phead!=NULL){
        q=phead->next;
        phead->next=NULL;
        free(phead);
        phead=q;
    }
}


void showpage(Link *list) {
    Link *t;
    //printf("the list is: \n");
    for(t = list; t!= NULL; t = t ->next){
        printf("%d\n",t->url);
    }
}

Nodeb *readSection2(char *urlname){
/*
   let's say filename is "url31.txt"
   Open "url31.txt"
   read Section-2
	(How?, a simple approach ...
	 skip lines until first two tokens are "#start" and  "Section-2"
	 read lines (tokens) and add  words (normalised) in inverted index ADT idx
	 stop reading when first two tokens are "#end" and  "Section-2"
	)
*/
    int i , j;
    Nodeb *word = NULL ;          // store words in node word and return word
    char delim[2] = " ";
    char *token;
    char line[MAXSTRING] ;


    FILE *f;
    char file[64] = {0};
    sprintf(file, "/Users/wangxiaoyu/CLionProjects/untitled1/assignment/%s.txt", urlname);
    if ((f = fopen (file, "r")) == NULL) {
        printf("file %s opens error!\n", urlname);
    }

    // process urlname to int
    // move 3 units towards left
    for(j=0; j<3;j++){
        for(i=0; urlname[i]!='\0';i++) {
            urlname[i]=urlname[i+1];
        }
        urlname[i]=urlname[i+1];
    }
    int page = atoi(urlname);

    int read=0;
    int count = 0;      // count the num of head pointer of double linked list
    Nodeb *singleword;

    while(fgets(line, MAXSTRING, f) != NULL) {

        /* first token */
        unsigned long int len;
        len = strlen(line);
        line[len-1] = '\0';                              // delete blank line

        token = strtok(line, delim);
        if ((strcmp(line, "#end")==0) && read == 1){
            read = 0;
            break;
        }
        if (token!=NULL && read ==1){               // readable area
            len = strlen(token);
//            printf(" length of word is : %d\n", len);
            if ((token[len-1]=='.') || (token[len-1]==',') || (token[len-1]==';') ||(token[len-1]=='?')) {
                token[len-1] = '\0';
            }
            for(i=0;token[i]!='\0';i++){
                token[i]= tolower(token[i]);
            }

//            printf("%s\n",token);
            if (count ==0){
                word = Makenodeb(token);
                word->l = insertListOrder(word->l,page);
                count++;
                // printf("start : %s\n",singleword->data);
            }else {
                singleword =  Makenodeb(token);
//                printf("%s\n",singleword->data);
                if (!(ifnodeexistb(word, singleword))){
                    word = insertRb(word, singleword);
                    singleword->l = insertListOrder(singleword->l,page);
                    count++;
                }
            }
        }
//        printf("%d\n", count);
        while(token!=NULL) {

            /* rest token */
            if (strcmp(token, "Section-2")==0) {
                read = 1;
            }
            token = strtok(NULL, delim);

            if (token!=NULL && read ==1){

                // delete . , ; ?
                len = strlen(token);
                if ((token[len-1]=='.') || (token[len-1]==',') || (token[len-1]==';') ||(token[len-1]=='?')) {
                    token[len-1] = '\0';
                }
//                printf("%s\n",token);

                // convert to lower letters
                for(i=0;token[i]!='\0';i++){
                    token[i]= tolower(token[i]);
                }

//                printf("%s\n",token);
                if (count == 0){
                    word = Makenodeb(token);

                    word->l = insertListOrder(word->l,page);
                    count++;
                }else {
//                    printf("%s\n",token);
                    singleword =  Makenodeb(token);
                    if (!(ifnodeexistb(word, singleword))){
                        word = insertRb(word, singleword);
                        singleword->l = insertListOrder(singleword->l,page);
                        count++;
//                        printf("new word: %s\n", token);
                    }
                }
            }
        }

    }
    // showlist(word);
//    printf("%d\n", count);
    return word;
}



Nodeb *addpagelinkb(Nodeb *list, Nodeb *new){
    Nodeb *a;
    for(a = list; a!=NULL; a = a->next){
        if (strcmp(a->data, new->data)==0) {
            a->l = insertListOrder(a->l,new->l->url);
            break;
        }
    }
    return list;
}

Nodeb *addlinkedlistb(Nodeb *list, Nodeb *addlist){
    Nodeb *wordList = list;

    Nodeb *curr = addlist;
    Nodeb *single;
    while(curr !=NULL){
        if (!(ifnodeexistb(wordList, curr))) {     // new word add into linked list
//            printf("new word is : %s\n", curr->data);
            single = Makenodeb(curr->data);
            single->l = curr->l;
            wordList = newinsertRb(wordList, single);

        }else{                           // existed word, add page link
            single = Makenodeb(curr->data);
            single->l = curr->l->next;

            wordList = addpagelinkb(wordList, single);
        }
        curr = curr->next;
    }
//    printf("%d\n",lengthlist(wordList));
//    showlist(wordList);

    return wordList;

}


void freepointb(Nodeb *list){
    if (list != NULL) {
        freepointb(list->next);
        free(list);
    }
}

void freelinkb(Link *list){
    if (list != NULL) {
        freelinkb(list->next);
        free(list);
    }
}
