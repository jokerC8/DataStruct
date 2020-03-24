#include <stdio.h>
#include <unistd.h>

#include "queue.h"

void *rroutine(void *queue)
{
	queue = (Queue*)queue;
	pthread_t pid;

	pid = pthread_self();

	for (; ;) {
		fprintf(stdout, "%d\n", FontAndDequeue(queue));
		usleep(1000 * 10);
	}
}

void *wroutine(void *queue)
{
	queue = (Queue *)queue;
	pthread_t pid;

	pid = pthread_self();

	for (; ;) {
		Enqueue(pid, queue);
		usleep(1000 * 10);
	}
}

static void test()
{
	unsigned int i;
	Queue Q;
	pthread_mutex_t lock;
	pthread_t pids[10];

	pthread_mutex_init(&lock, NULL);
	Q = CreateQueue(0x10000, &lock);

	for (i = 0; i < sizeof(pids)/sizeof(pthread_t); i++) {
		if (i < 8)
			pthread_create(&pids[i], NULL, wroutine, Q);
		else
			pthread_create(&pids[i], NULL, rroutine, Q);
	}

	for (i = 0; i < sizeof(pids)/sizeof(pthread_t); i++)
		pthread_join(pids[i], NULL);
}

int main(void)
{
	test();

	return 0;
}
