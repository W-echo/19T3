//
// Created by 王晓雨 on 17/1/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
#define MAXSTRING 1000
#define MAXPAGE 30


int main(int argc, char *argv[]) {
    char delim[2] = " ";
    char *token;
    char line[MAXSTRING] ;
    FILE *f;
                                                            // read collection.txt
    if ((f = fopen ("/Users/wangxiaoyu/CLionProjects/untitled1/assignment/collection.txt", "r")) == NULL) {
        printf("Error!\n");
        return (0);
    }
    Nodea *List_of_Urls;                                                // *t:pointer to the name of all urlxx.txt
    int lnCount = 0;

    while(fgets(line, MAXSTRING, f) != NULL) {
        /* first token */

        unsigned long int len;
        len = strlen(line);
        line[len-1] = '\0';                              // delete blank line
        token = strtok(line, delim);

        if (token!=NULL){                           //  makenode or insert
            if (lnCount==0){
                List_of_Urls = Makenodea(token);
            } else{
                insertEnda(List_of_Urls,token);
            }
            lnCount++;
        }


        /* iterate over the rest of the tokens */
        while(token!=NULL ) {
            token = strtok(NULL, delim);
            if (token!=NULL){                           //  makenode or insert
                if (lnCount==0){
                    List_of_Urls = Makenodea(token);
                } else{
                    insertEnda(List_of_Urls,token);
                    lnCount++;
                }
            }
        }
    }
//    showlist(List_of_Urls);

    int len=lengthlista(List_of_Urls);       //num of graph nV
    //printf("%d\n",len);
    Graph g;                               // pointer to graph
    g = newGraph(len);
    Nodea *p = List_of_Urls;


    // read section-1 for out links
    for (int i=0; i<len;i++){
        readSection1(List_of_Urls,p->data, g);
        p = p->next;
    }


    // pagerank algorithm : calculate the weight of every urlxx.txt
    for (int i=0; i<len; i++) {
        if (adjacent(g,2,i)) {
            //printf("%d\n", i);
        }
    }
    Wresult *res;
    //printf("%s\n", indexnum(1,List_of_Urls));
    res = PageRank(atof(argv[1]),atof(argv[2]),atoi(argv[3]), List_of_Urls, g);
    // res = PageRank(0.85,0.00001,1000,List_of_Urls, g);
    res = sortwei(res);
//    showwresult(res);

    // make file named pagerankList.txt
    FILE *fpWrite=fopen("pagerankList.txt","w");

    if(fpWrite==NULL) {return 0;}
    while(res!=NULL){
        fprintf(fpWrite,"%s, %d, %.7f\n",res->data,res->outdeg,res->weight);
        res = res->next;
    }
    fclose(fpWrite);

    // free pointers
    freepointa(List_of_Urls);
    free(g);
    freewresult(res);
}



