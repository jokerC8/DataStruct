#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "rbtree.h"

void test1()
{
	int i;
	int c;
	RBTree T = NULL;

	for (i = 0; i < 30; i++) {
		c = random()%1000;
		T = Insert(c, T);
	}
	InOrder(T);
	while (T) {
		c = Retrive(FindMin(T));
		fprintf(stdout, "Delete a num:%d\n", c);
		fprintf(stdout, "---------------------------------------\n");
		Delete(c, &T);
		InOrder(T);
	}
}

void tt()
{
	int i;
	RBTree T = NULL;

	for (i = 0; i < 100; i++)
		T = Insert(i, T);
	for (i = 0; i < 100; i++)
		T = Insert(i, T);
	while (T) {
		Delete(Retrive(FindMax(T)), &T);
	}
	InOrder(T);
}
#if 0
void test()
{
	int i;
	RBTree T = NULL;
	int nums[] = {100, 50, 200, 40, 80, 150, 250, 45, 30, 60, 90, 120, 180, 220, 260, 25, 35, 44, 49, 55, 70, 88, 92, 118, 130, 160, 190, 210, 230, 255, 300};

	for (i = 0; i < 31; i++) {
		T = BuildTreeForTest(nums[i], T);
	}
	InOrder(T);
	while (T) {
		i = nums[random()%31];
		fprintf(stdout, "Delete a num:%d\n", i);
		Delete(i, &T);
		InOrder(T);
	}
}
#endif
void t()
{
	int c;
	RBTree T = NULL;

	T = BuildTreeForTest(100, 1, T);
	T = BuildTreeForTest(60, 1, T);
	T = BuildTreeForTest(50, 1, T);
	T = BuildTreeForTest(80, 0, T);
	T = BuildTreeForTest(70, 1, T);
	T = BuildTreeForTest(90, 1, T);
	T = BuildTreeForTest(66, 0, T);
	T = BuildTreeForTest(75, 0, T);
	T = BuildTreeForTest(150, 1, T);
	T = BuildTreeForTest(130, 0, T);
	T = BuildTreeForTest(120, 1, T);
	T = BuildTreeForTest(140, 1, T);
	T = BuildTreeForTest(135, 0, T);
	T = BuildTreeForTest(145, 0, T);
	T = BuildTreeForTest(180, 1, T);
	InOrder(T);
#if 0
	while (1) {
		fprintf(stdout, "Please input a num:");
		scanf("%d", &c);
		T = Insert(c, T);
		InOrder(T);
		if (c == 1024)
			break;
	}
#endif
	while (T) {
		fprintf(stdout, "Delete a num:");
		scanf("%d", &c);
		Delete(c, &T);
		InOrder(T);
	}
}

int main(void)
{
//	test();

	test1();
	return 0;
}
