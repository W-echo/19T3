//
// Created by 王晓雨 on 18/1/20.
//

#include "graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSTRING 1000

Graph newGraph(int V){
    assert(V >= 0);

    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);
    g->nV = V;
    g->nE = 0;
    g->edges = malloc(V * sizeof(int *));       // allocate memory for each row
    assert(g->edges != NULL);
    int i;
    for (i = 0; i < V; i++) {
        g->edges[i] = calloc(V, sizeof(int));       // allocate memory for each column and initialise with 0
        assert(g->edges[i] != NULL);
    }
    return g;
}

bool validV(Graph g, Vertex v) {
//    bool x = g!=NULL && v>=0 && v < g->nV;
//    printf("%d",x);
    return (g!=NULL && v>=0 && v < g->nV);
}

void insertEdge(Graph g, Edge e) {
    assert(g!=NULL && validV(g,e.v) && validV(g,e.w));
    if(g->edges[e.v][e.w]==0) {
        //printf("insert success");
        g->edges[e.v][e.w]= 1;
        //g->edges[e.w][e.v]= 1;
        g->nE++;
    }
}


void  removeEdge(Graph g, Edge e) {
    assert(g!=NULL && validV(g,e.v) && validV(g,e.w));
    if(g->edges[e.v][e.w]==1) {
        g->edges[e.v][e.w]= 0;
        g->edges[e.w][e.v]= 0;
        g->nE--;
    }
}

bool adjacent(Graph g, Vertex x, Vertex y) {     /* is there an edge between two vertices */
    assert(g!=NULL && validV(g,x) && validV(g,y));
    return (g->edges[x][y]);
}

void  freeGraph(Graph g) {
    free(g);
}

void readSection1(Nodea *list, char *urlname, Graph g) {
/*
   let's say urlname is "url31"
   Open "url31.txt"
   read Section-1
	(How?, a simple approach ...
	 skip lines until first two tokens are "#start" and  "Section-1"
	 read lines (tokens) and add the required links in graph g
	 stop reading when first two tokens are "#end" and  "Section-1"
	)
*/
    Edge e;
    int i = 0;

    char delim[2] = " ";
    char *token;
    char line[MAXSTRING] ;


    FILE *f;
    char file[64] = {0};
    sprintf(file, "/Users/wangxiaoyu/CLionProjects/untitled1/assignment/%s.txt", urlname);
    if ((f = fopen (file, "r")) == NULL) {
        printf("file opens error!\n");
    }


    int read=0;                   // flag notice for read line or not : 0 or 1
    int x,y;                    // graph index num for add edge
    x = indexnodea(list,urlname);
    while(fgets(line, MAXSTRING, f) != NULL) {
        /* first token */
        int len;
        len = strlen(line);
        line[len-1] = '\0';                              // delete blank line
        token = strtok(line, delim);

        if (strcmp(line, "#end")==0){
            read = 0;
            break;
        }

        if (token!=NULL && read ==1){
            y = indexnodea(list,token);
            //printf("y=%s\n",token);
            e.v=x; e.w=y; insertEdge(g,e);
            //printf("x=%d, y=%d\n", x,y);
        }

        while(token!=NULL) {
            if (strcmp(token, "Section-1")==0) {
                read = 1;
            }
            token = strtok(NULL, delim);
            if (token!=NULL && read ==1){
                y = indexnodea(list,token);
                //printf("y=%s   ",token);
                e.v=x; e.w=y; insertEdge(g,e);
                //printf("x=%d, y=%d\n", x,y);
            }
        }
    }
}

char *indexnuma(int n, Nodea *list) {
    Nodea *p = list;
    int i = 0;
    while (i!=n){
        p = p->next;
        i++;
    }
    return p->data;

}



Wresult *Makewresult(char *x, int y, float z){
    Wresult *new = malloc(sizeof(Wresult));
    assert((new != NULL));
    strcpy(new->data,x);
//    printf("%s\n",new->data);
    new->outdeg = y;
    new->weight = z;
    new->next =NULL;
    return new;
}


void insertWresult(Wresult *list, Wresult *new) {

    while(list->next != NULL){
        list = list->next;
    }
    list->next = new;                    // create new element data
}

Wresult *PageRank(float d, float diffPR,int maxIterations, Nodea *p, Graph g){
    int N = lengthlista(p);
    float PRlast[N];           // store the last iteration result
    float PRnow[N];            // store iteration result now
    int iteration =0;
    float diff = diffPR;    // to enter the while loop
    int i,j,k;             // used for (while and for)
    int M[N], L;         // M: pointing to Pi   L: out degree of Pj
    int num;             // actual length of M
    float PRpart2;       // the second part of PR(Pi, t+1)
    while(iteration < maxIterations && diff>=diffPR){
        if (iteration==0){
            for (i=0; i<N; i++){
                PRlast[i]=(float)1/N;
            }
        }
        iteration++;
        if(iteration!=0) {
            for (i=0; i<N; i++){
                num = 0;
                for (j=0; j<N; j++) {
                    if (adjacent(g,j,i)) {              // url**(j) pointing to Pi
                        M[num]=j;
                        num++;
                    }
                }
                //printf("pointing to list[%d] = %d\n",i,num);

                PRpart2 =(float) 0;
                for (j=0; j< num; j++){             // L: out degree of M[j}
                    L=0;
                    for(k=0;k<N; k++){
                        if (adjacent(g, M[j],k)) {
                            L++;
                        }
                    }
                    //printf("list[%d]'s out deg = %d\n",M[j],L);
                    PRpart2 = PRpart2 + PRlast[M[j]] / (float)L;
                }

                PRnow[i]= ((float)1-d)/(float)N + d* PRpart2;
                //printf("iteration %d : %.7f\n",iteration,PRnow[i]);
            }

            diff= (float)0;
            for (i=0; i<N; i++){
                diff = diff + fabs(PRlast[i] - PRnow[i]);
                PRlast[i] = PRnow[i];

            }
        }

    }
    Wresult *result = NULL;
    char *page;
    for (i=0; i<N; i++){
//        printf("%s ",indexnum(i,p));
        page =indexnuma(i,p);
//        printf("%s\n",page);
        L = 0;
        for (j=0; j< N; j++) {             // L: out degree of p[i]
            if (adjacent(g, i, j)) {
                L++;
            }
        }
//        printf("%d, ",L);
//        printf("%.7f\n",PRnow[i]);
        if (result ==NULL){
            result = Makewresult(page, L,PRnow[i]);
        }else{
            insertWresult(result, Makewresult(page, L,PRnow[i]));
        }
    }
//    showwresult(result);
    return result;
}

void showwresult(Wresult *x){
    Wresult *p ;
    for(p = x; p!= NULL; p = p ->next){
        printf("%s %d %.7f\n",p->data,p->outdeg, p->weight);
    }
}

int length(Wresult *list){
    int i = 0;
    while(list!=NULL){
        list = list->next;
        i++;
    }
    return i;
}

Wresult *sortwei(Wresult *list){
    int len = length(list);
    Wresult *x, *y;
    char data[MAXWORD];
    float weight;
    int outdeg;
    int i,j;
    for(i=0; i<len-1; i++){
        j=0;
        for(y = list; j<len-1-i; y = y->next){
            if (y->weight<y->next->weight){
                strcpy(data,y->data); weight = y->weight; outdeg = y->outdeg;
                strcpy(y->data,y->next->data); y->weight = y->next->weight; y->outdeg = y->next->outdeg;
                strcpy(y->next->data,data); y->next->weight = weight; y->next->outdeg = outdeg;
            }
            j++;
        }
    }
    return list;
}

void freepointa(Nodea *list){
    if (list != NULL) {
        freepointa(list->next);
        free(list);
    }
}

void freewresult(Wresult *list){
    if (list != NULL) {
        freewresult(list->next);
        free(list);
    }
}