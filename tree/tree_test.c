#include <stdio.h>
#include "tree.h"

int main(void)
{
	unsigned i;
	int scores[] = {66, 90, 78, 36, 56, 89, 99, 23};
	Position Min, Max;

	Tree T = NULL;

	for (i = 0; i < sizeof(scores)/sizeof(int); i++)
		T = Insert(scores[i], T);
	Min = FindMin(T);
	Max = FindMax(T);
	fprintf(stdout, "min=%d max=%d\n", Retrive(Min), Retrive(Max));
	PrintTree(T);
	fprintf(stdout, "\nHeight=%d\n", Height(T));
	Delete(Retrive(Min), T);
	Delete(Retrive(Max), T);
	Min = FindMin(T);
	Max = FindMax(T);
	fprintf(stdout, "min=%d max=%d\n", Retrive(Min), Retrive(Max));
	PrintTree(T);
	Delete(89, T);
	fprintf(stdout, "\nHeight=%d\n", Height(T));
	return 0;
}
