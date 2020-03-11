//
// Created by 王晓雨 on 14/1/20.
//

#include <stdio.h>
#include <string.h>
#include "partc.h"
#include <stdlib.h>
#include <assert.h>
#define MAXSTRING 1000
#define MAXPAGE 30

int main(int argc, char** argv) {

    int num = argc - 1;         // numbers of search words: num
    int i;
    Nodec **p;                   // pointers to search words
    Sample *result = NULL ;
    p = malloc(num*sizeof(Nodec*));          //linked list of search word(head) and pages
    assert(p != NULL);
    for (i=0;i<num;i++){
        p[i]=calloc(MAXSTRING,sizeof(Nodec));
        assert(p[i] != NULL);
    }


    // open invertedIndex.txt and process word and page
    char delim[2] = " ";
    char *token;
    char line[MAXSTRING] ;
    FILE *f;

    if ((f = fopen ("/Users/wangxiaoyu/CLionProjects/untitled1/assignment/invertedIndex.txt", "r")) == NULL) {
        printf("Error!\n");
        return (0);
    }


    int lnCount = 0;
    char *s;
    Nodec *singlelink;
    while(fgets(line, MAXSTRING, f) != NULL)  {
        unsigned long int len;
        len = strlen(line);
        line[len-1] = '\0';
        token = strtok(line, delim);            /* first token */
        s =token;

        if (indexwordc(argv, s)) {
            //printf("the search word is %s\n", s);
            p[lnCount] = Makenodec(s);        //search word as head pointer of linked list
            //showlist(p[lnCount]);

            while( token != NULL ) {                //store lines containing the search words
                token = strtok(NULL, delim);
                s=token;
                //printf( "%s\n", s);
                if (token!= NULL) {
                    insertEndc(p[lnCount], s);
                }
            }
            singlelink = p[lnCount]->next;
            while(singlelink!=NULL){
//                printf("%s\n",singlelink->data);
                if(result==NULL){
                    result = Makesample(singlelink->data);
                }else{
                    if(!ifexistsample(result,singlelink->data)){
                        result = addsample(result, singlelink->data);
                    }
                }
                singlelink =singlelink->next;
            }
//            showresult(result);
//            showlist(p[lnCount]);
            lnCount++;
        }
    }


    // open pagerankList.txt and process word and page
    char del[] = ", ";
    if ((f = fopen ("/Users/wangxiaoyu/CLionProjects/untitled1/assignment/pagerankList.txt", "r")) == NULL) {
        printf("Error!\n");
        return (0);
    }

    rank *pageRank = NULL;
    rank *single= NULL;
    char *page = NULL;
//    printf("%s %.7f\n", pageRank->page, pageRank->weight);
    float t;
    while(fgets(line, MAXSTRING, f) != NULL)  {
        unsigned long int len;
        len = strlen(line);
        line[len-1] = '\0';

        token = strtok(line, del);
        page = token;
//        printf("%s --- ", token);
        lnCount = 0;
        while(token != NULL) {
            token = strtok(NULL, del);
//            printf("%s ", token);
            lnCount++;

            if (lnCount==2 && token != NULL){
                t = atof (token);
                single = Makerank(line, t);
                if(pageRank ==NULL){
                    pageRank =single;
                }else{
                    pageRank = append(pageRank,single);
                }

            }
        }

    }
    rank *r = pageRank;

    while(r!=NULL){
        result = addweight(result,r);
//        printf("%s %.7f\n", r->page, r->weight);
        r = r->next;
    }


    // sort the result list
    /* first step: sorted by number count  */
//    showresult(result);
    result= sortcount(result);
//    showresult(result);
    /* second step: sorted by weight in the same count  */
    result = sortweight(result);
//    showresult(result);

    // show the first 30 search result
    i = 1;
    while(result!=NULL||i>MAXPAGE){
//        if (result == NULL){ return 0;}
//        else{
        printf("%s\n",result->page);
        i++;
        result = result->next;
    }

    // free pointers


    for (i=0;i<num;i++){
        freepointc(p[i]);
    }
//    printf("free p[i]");
    free(p);
//    printf("free p");

    freesample(result);
    freerankc(pageRank);


}


















