//
// Created by 王晓雨 on 21/1/20.
//

# include "partb.h"
# include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>



int main() {
    char delim[2] = " ";
    char *token;
    char line[MAXSTRING] ;
    FILE *f;

    // read collection.txt
    if ((f = fopen ("/Users/wangxiaoyu/CLionProjects/untitled1/assignment/collection.txt", "r")) == NULL) {
        printf("Error!\n");
        return (0);
    }
    Nodeb *List_of_Urls= NULL;

    int lnCount = 0;

    while(fgets(line, MAXSTRING, f) != NULL) {
        /* first token */

        unsigned long int len;
        len = strlen(line);
        line[len-1] = '\0';                         // delete blank line
        token = strtok(line, delim);

//        printf("line: %s\n",token);
        if (token!=NULL){                           //  makenode or insert
            if (lnCount==0){
                List_of_Urls = Makenodeb(token);
                lnCount++;

//                printf("%d\n", lengthlist(List_of_Urls));
            } else{
                insertEndb(List_of_Urls,token);
//                printf("%d\n", lengthlist(List_of_Urls));
                lnCount++;
            }
            //printf("count = %d\n", lnCount);
        }
        /* iterate over the rest of the tokens */
        while(token!=NULL ) {
            token = strtok(NULL, delim);

//            printf("token: %s\n",token);
            if (token!=NULL){                           //  makenode or insert
                if (lnCount==0){
                    List_of_Urls = Makenodeb(token);
                    lnCount++;
                } else{
                    insertEndb(List_of_Urls,token);
//                    printf("x:%d\n", lengthlist(List_of_Urls));
                    lnCount++;
                }
                //printf("count = %d\n", lnCount);

            }
        }
    }
//    printf("%d\n",lnCount);
//    showlist(List_of_Urls);
    int len=lengthlistb(List_of_Urls);
//    printf("%d\n",len);

//    Node *w = NULL;        //pointer to words
    Link *l ;
//            malloc(sizeof(Link *));        // pointer to links
//    assert(l != NULL);
//    l->next = NULL;

    // read section-2 for out links
    //int i = 0;
    Nodeb *word = NULL;
//            malloc(sizeof(Nodeb *));          // store all words
//    assert(word!=NULL);
//    word->l = NULL;
//    word->next = NULL;


    Nodeb **txt;
    txt = malloc(len * sizeof(Nodeb *));
    assert(txt !=NULL);
    for (int i = 0; i < len; i++) {
        txt[i] = NULL;
//                malloc(sizeof(Nodeb));
//        assert(txt[i] != NULL);
    }
    int count =0;
    for (Nodeb *p = List_of_Urls; p != NULL;p = p->next) {
        txt[count] = readSection2(p->data);
        // show words in every txt
//        printf("\nThe %sst file:\n", p->data);
//        showlist(txt[count]);
        if (count ==0){
            word = txt[count];
        }else {
            word = addlinkedlistb(word, txt[count]);
        }
        count++;
    }

//    showlist(word);
//    printf("%d\n",lengthlist(word));


    FILE *fpWrite=fopen("invertedIndex.txt","w");

    if(fpWrite==NULL) {return 0;}
    Nodeb *t ;
    for(t = word; t!=NULL; t=t->next) {
        fprintf(fpWrite,"%s  ",t->data);
//        printf("%s: ", t->data);
        Link *li;
        for (li = t->l->next; li != NULL; li = li->next) {
//            printf("%d ", li->url);
            fprintf(fpWrite,"url%d ",li->url);
        }
//        printf("\n");
        fprintf(fpWrite,"\n");
    }

    fclose(fpWrite);

    // free pointers


    freelinkb(l);
    for(int i = 0; i < len; i++){
        freepointb(txt[i]);
    }
    free(txt);
    freepointb(List_of_Urls);





}