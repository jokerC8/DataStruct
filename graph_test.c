#include "graph.h"

static void test()
{
	Graph G;

	G = InitGraph(20);
	AddEdg(1, 2, 1, 1, G);
	AddEdg(1, 3, 1, 1, G);
	AddEdg(1, 4, 1, 1, G);
	AddEdg(2, 4, 1, 1, G);
	AddEdg(2, 5, 1, 1, G);
	AddEdg(5, 7, 1, 1, G);
	AddEdg(7, 6, 1, 1, G);
	AddEdg(6, 3, 1, 1, G);
	AddEdg(4, 3, 1, 1, G);
	AddEdg(4, 5, 1, 1, G);
	AddEdg(4, 6, 1, 1, G);
	AddEdg(4, 7, 1, 1, G);
	PrintGraph(G);
	DestroyGraph(G);
}

int main(void)
{
	test();

	return 0;
}
