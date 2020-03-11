//
// Created by 王晓雨 on 18/1/20.
//
#include <stdbool.h>
#include "parta.h"
#include <math.h>
#ifndef ASSIGNMENT_GRAPH_H
#define ASSIGNMENT_GRAPH_H

#endif //ASSIGNMENT_GRAPH_H


typedef int Vertex;
// edges are pairs of vertices (end-points)
typedef struct Edge {
    Vertex v; Vertex w;
}Edge;

typedef struct GraphRep {
    int  **edges; // adjacency matrix
    int    nV;    // num of vertices
    int    nE;    // edges
}GraphRep;

// graph representation is hidden
typedef struct GraphRep *Graph;



void readSection1(Nodea *list, char *urlname, Graph g);

// operations on graphs
Graph newGraph(int V);              // new graph with V vertices
bool validV(Graph g, Vertex e);      //check if vertex is valid
void  insertEdge(Graph g, Edge e);
void  removeEdge(Graph g, Edge e);
bool  adjacent(Graph g, Vertex x, Vertex y); /* is there an edge between two vertices */
void  freeGraph(Graph g);


Wresult *PageRank(float d,float diffPR,int maxIterations,Nodea *p, Graph g);  // pagerank algorithm
char *indexnuma(int n, Nodea *list);                  // return the index number of a node in linked list p
void freepointa(Nodea *list);
void freewresult(Wresult *list);