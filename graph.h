#ifndef __GRAPH_H
#define __GRAPH_H

struct GraphStruct;
typedef struct GraphStruct *Graph;

Graph InitGraph(int Size);
void PrintGraph(Graph G);
void DestroyGraph(Graph G);
void WeightedPathLength(Graph G);
void AddEdg(int Src, int Dest, int weight, int Directed, Graph G);

#endif
