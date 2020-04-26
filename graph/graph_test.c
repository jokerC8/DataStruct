#include "graph.h"

#define WEIGHTED

static void test()
{
	Graph G;

	G = InitGraph(8);
#if defined(WEIGHTED)
	AddEdg(1, 2, 2, 1, G);
	AddEdg(1, 4, 1, 1, G);
	AddEdg(2, 4, 3, 1, G);
	AddEdg(2, 5, 10, 1, G);
	AddEdg(3, 1, 4, 1, G);
	AddEdg(3, 6, 5, 1, G);
	AddEdg(4, 3, 2, 1, G);
	AddEdg(4, 5, 2, 1, G);
	AddEdg(4, 6, 8, 1, G);
	AddEdg(4, 7, 4, 1, G);
	AddEdg(5, 7, 6, 1, G);
	AddEdg(6, -1, 0, 1, G);
	AddEdg(7, 6, 1, 1, G);
	WeightedPathLength(1, G);
#else
	AddEdg(1, 2, 1, 1, G);
	AddEdg(1, 4, 1, 1, G);
	AddEdg(2, 4, 1, 1, G);
	AddEdg(2, 5, 1, 1, G);
	AddEdg(3, 1, 1, 1, G);
	AddEdg(3, 6, 1, 1, G);
	AddEdg(4, 3, 1, 1, G);
	AddEdg(4, 5, 1, 1, G);
	AddEdg(4, 6, 1, 1, G);
	AddEdg(4, 7, 1, 1, G);
	AddEdg(5, 7, 1, 1, G);
	AddEdg(7, 6, 1, 1, G);
	UnWeightedPathLength(1, G);
#endif

	PrintGraph(G);
	DestroyGraph(G);
}

int main(void)
{
	test();

	return 0;
}
