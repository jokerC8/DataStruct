#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"
#include "graph.h"

#define NotAVertex (-1)
#define Infinity (0x7fffffff)

struct AdjListNode {
	int Dest;
	int Weight;
	struct AdjListNode *next;
};

struct TableEntry {
	int Dist;
	int Path;
	int Known;
	struct AdjListNode *head;
};

struct GraphStruct {
	int Size;
	struct TableEntry *entrys;
};

Graph InitGraph(int Size)
{
	int i;
	Graph G;

	G = malloc(sizeof(*G));
	if (!G)
		return NULL;
	G->entrys = malloc(Size * sizeof(struct TableEntry));
	G->Size = Size;
	for (i = 0; i < Size; i++) {
		G->entrys[i].Dist = Infinity;
		G->entrys[i].Path = NotAVertex;
		G->entrys[i].head = NULL;
		G->entrys[i].Known = 0;
	}

	return G;
}

void AddEdg(int Src, int Dest, int Weight, int Directed, Graph G)
{
	struct AdjListNode *node;

	/* if graph not directed, ignore weight */
	if (Src > G->Size || Dest > G->Size)
		return;
	if (Directed) {
		if (Dest > 0) {
			node = malloc(sizeof(*node));
			if (node) {
				node->Dest = Dest;
				node->Weight = Weight;
				node->next = G->entrys[Src].head;
				G->entrys[Src].head = node;
			}
		}
	} else {
		node = malloc(sizeof(*node));
		if (node) {
			node->Dest = Dest;
			node->next = G->entrys[Src].head;
			G->entrys[Src].head = node;
		}
		node = malloc(sizeof(*node));
		if (node) {
			node->Dest = Src;
			node->next = G->entrys[Dest].head;
			G->entrys[Dest].head = node;
		}
	}
}

void PrintGraph(Graph G)
{
	int i;
	struct AdjListNode *node;

	for (i = 0; i < G->Size; i++) {
		node = G->entrys[i].head;
		if (!node)
			continue;
		if (node)
			fprintf(stdout, "Dist=%d Path=%d\n\t", G->entrys[i].Dist, G->entrys[i].Path);
		while (node) {
			fprintf(stdout, "[%d -> %d weight=%d]", i, node->Dest, node->Weight);
			node = node->next;
		}
		putchar('\n');
	}
}

void DestroyGraph(Graph G)
{
	int i;
	struct AdjListNode *node, *next;

	for (i = 0; i < G->Size; i++) {
		if (!G->entrys[i].head)
			continue;
		for (node = G->entrys[i].head; node && node->next; node = next) {
			next = node->next;
			free(node);
		}
	}
	/* free nodes */
	free(G->entrys);
	G->entrys = NULL;
}

void WeightedPathLength(int StartVertex, Graph G)
{
	int i, j, temp, Vertex;
	struct AdjListNode *node;

	if (StartVertex > G->Size)
		return;
	G->entrys[StartVertex].Dist = 0;
	for (i = 0 ; i < G->Size; i++) {
		temp = Infinity;
		for (j = 0; j < G->Size; j++) {
			if (G->entrys[j].Known)
				continue;
			if (G->entrys[j].Dist < temp) {
				temp = G->entrys[j].Dist;
				Vertex = j;
			}
		}
		node = G->entrys[Vertex].head;
		G->entrys[Vertex].Known = 1;
		while (node) {
			if (!G->entrys[node->Dest].Known) {
				if (G->entrys[node->Dest].Dist > (G->entrys[Vertex].Dist + node->Weight))
					G->entrys[node->Dest].Dist = G->entrys[Vertex].Dist + node->Weight;
					G->entrys[node->Dest].Path = Vertex;
			}
			node = node->next;
		}
	}
}

void UnWeightedPathLength(int StartVertex, Graph G)
{
	Queue Q;
	int Vertex;
	struct AdjListNode *node;

	if (StartVertex > G->Size)
		return;
	Q = CreateQueue(G->Size * 2);
	G->entrys[StartVertex].Dist = 0;
	G->entrys[StartVertex].Known = 1;
	Enqueue(StartVertex, Q);
	while (!IsEmpty(Q)) {
		Vertex = FontAndDequeue(Q);
		node = G->entrys[Vertex].head;
		while (node) {
			if (!G->entrys[node->Dest].Known) {
				G->entrys[node->Dest].Known = 1;
				G->entrys[node->Dest].Dist = G->entrys[Vertex].Dist + node->Weight; 
				Enqueue(node->Dest, Q);
				G->entrys[node->Dest].Path = Vertex;
			}
			node = node->next;
		}
	}
}
