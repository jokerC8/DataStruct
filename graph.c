#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

struct AdjListNode {
	int Dest;
	int weight;
	struct AdjListNode *next;
};

struct GraphStruct {
	int Size;
	struct AdjListNode **nodes;
};

Graph InitGraph(int Size)
{
	Graph G;

	G = malloc(sizeof(*G));
	if (!G)
		return NULL;
	G->nodes = malloc(Size * sizeof(struct AdjListNode *));
	bzero(G->nodes, Size * sizeof(struct AdjListNode *));
	G->Size = Size;

	return G;
}

void AddEdg(int Src, int Dest, int weight, int Directed, Graph G)
{
	struct AdjListNode *node;

	/* if graph not directed, ignore weight */
	if (Directed) {
		node = malloc(sizeof(*node));
		if (node) {
			node->Dest = Dest;
			node->weight = weight;
			node->next = G->nodes[Src];
			G->nodes[Src] = node;
		}
	} else {
		node = malloc(sizeof(*node));
		if (node) {
			node->Dest = Dest;
			node->next = G->nodes[Src];
			G->nodes[Src] = node;
		}
		node = malloc(sizeof(*node));
		if (node) {
			node->Dest = Src;
			node->next = G->nodes[Dest];
			G->nodes[Dest] = node;
		}
	}
}

void PrintGraph(Graph G)
{
	int i;
	struct AdjListNode *node;

	for (i = 0; i < G->Size; i++) {
		node = G->nodes[i];
		if (!node)
			continue;
		while (node) {
			fprintf(stdout, "[%d -> %d]", i, node->Dest);
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
		if (!G->nodes[i])
			continue;
		for (node = G->nodes[i]; node; node = next) {
			next = node->next;
			free(node);
		}
	}
	/* free nodes */
	free(G->nodes);
	G->nodes = NULL;
}

void WeightedPathLength(Graph G)
{

}
