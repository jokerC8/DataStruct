#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

#include "list.h"
#include "kfifo.h"

#define Logd(format, args...) fprintf(stdout, format, ##args)

#define SIZE 1024

uint8_t STOPBIT;

typedef struct Student {
    uint16_t u16Id;
    char name[30];
    uint8_t u8Age;
    uint8_t u8Sex;
    struct list_head list;
} Student;

static void listTest(int count)
{
    int i;
    Student *stu, *temp;
    struct list_head head;

    INIT_LIST_HEAD(&head);

    for (i = 0; i < count; i++) {
        stu = malloc(sizeof(Student));
        if (stu) {
            bzero(stu, sizeof(Student));
            stu->u16Id = i;
            stu->u8Age = i % 100;
            stu->u8Sex = i % 2;
            snprintf(stu->name, sizeof(stu->name) - 1, "My name is chen_%d", stu->u16Id);
            list_add(&stu->list, &head);
        }
    }

    list_for_each_entry_safe(stu, temp, &head, list) {
        list_del(&stu->list);
        Logd("u16Id=%d name=%s\n", stu->u16Id, stu->name);
        free(stu);
    }
}

typedef struct Family {
    uint8_t u8num;
    uint8_t u8id;
    char firstname[30];
    uint32_t u32income;
    struct hlist_node hlist;
} Family;

static void hlistTest(int count)
{
    int i;
    Family *fam;
    struct hlist_node *pos, *n;

    HLIST_HEAD(head);

    for (i = 0; i < count; i++) {
        fam = malloc(sizeof(Family));
        if (fam) {
            bzero(fam, sizeof(Family));
            fam->u32income = pow(2, 15);
            fam->u8num = 6;
            fam->u8id = i % 100;
            snprintf(fam->firstname, sizeof(Family), "chen_%d", fam->u8id);
            hlist_add_head(&fam->hlist, &head);
        }
    }
    hlist_for_each_entry_safe(fam, pos, n, &head, hlist) {
        hlist_del(&fam->hlist);
        Logd("u8id=%d name=%s\n", fam->u8id, fam->firstname);
        free(fam);
    }
    Logd("please enter any key to continue...");
    getchar();
}

void signal_handler(int signo)
{
    if (signo == SIGUSR1)
        STOPBIT = 1;
}

static int findSecondMax(int *array, int count)
{
    int i;
    int max, second, temp = 0;

    if (count == 1) return array[0];
    if (count == 2) return array[0] > array[1] ? array[1] : array[0];

    max = array[0];
    second = array[1];
    if (max < second) {
        temp = max;
        max = second;
        second = max;
    }
    for (i = 2; i < count; i++) {
        if (array[i] > max) {
            temp = max;
            max = array[i];
            second = temp;
        } else if (array[i] > second)
            second = array[i];
    }
    return second;
}

typedef struct Country {
	uint16_t u16Code;
	struct hlist_node hlist;
} Country;

static void hlistTest1(int count)
{
	int i = 0;
	Country *ct;
	struct hlist_node *pos, *n;

	HLIST_HEAD(hlist);

	if (count < 10) return;
	for (i = 0; i < count; i++) {
		if ((ct = malloc(sizeof(Country)))) {
			bzero(ct , sizeof(Country));
			ct->u16Code = i % 10000;
			hlist_add_head(&ct->hlist,&hlist);
		}
	}
	i = 0;
	hlist_for_each_entry_safe(ct, pos, n, &hlist, hlist) {
		if (i++ == 10) break;
	}
	Logd("continue from 10, not include 10\n");
	hlist_for_each_entry_continue(ct, pos, hlist) {
		Logd("u16Code=%d\n", ct->u16Code);
	}
	i = 0;
	hlist_for_each_entry_safe(ct, pos, n, &hlist, hlist) {
		if (i++ == 10) break;
	}
	Logd("continue from 10, include 10\n");
	hlist_for_each_entry_from(ct, pos, hlist) {
		Logd("u16Code=%d\n", ct->u16Code);
	}
	/* free all nodes */
	hlist_for_each_entry_safe(ct, pos, n, &hlist, hlist) {
		free(ct);
	}
}

static void sort(int *arr, int count)
{
  int i, j, temp;

  for (i = 0; i < count; i++) {
    for (j = i + 1; j < count; j++) {
      if (arr[i] > arr[j]) {
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
      }
    }
  }
}

static int binary_search(int *arr, int count, int target)
{
  int middle, left = 0, right = count - 1;

  while (left < right) {
    middle = (left + right)/2;
    if (arr[middle] < target) {
      left = middle + 1;
    } else {
      right = middle;
    }
  }
  if (arr[left] == target)
    return left;
  return -1;
}

static int binsearch(int *array, int left, int right, int target)
{
    int middle;

    if (left == right) {
        if (array[left] == target)
            return left;
        return -1;
    }
    middle = (left + right)/2;
    if (array[middle] >= target)
        right = middle;
    else
        left = middle + 1;
    return binsearch(array, left, right, target);
}

void *rroutine(void *args)
{
	char *str;
	char *words[] = {
		"hello, I am joker",
		"I am learning now",
		"I want to be better",
		"to be brave and honest",
		"make more money",
		"go home for sleep",
		"like c and python lanuage"
	};
	struct kfifo *fifo = (struct kfifo *)args;
	for (; ;) {
		str = words[rand() % (sizeof(words)/sizeof(char *))];
		fprintf(stdout, "write to kfifo:%s\n", str);
		kfifo_put(fifo, (unsigned char *)str, strlen(str));
		usleep(1000 * 10);
	}
}

void *wroutine(void *args)
{
	unsigned char buf[4096] = {0};
	struct kfifo *fifo = (struct kfifo *)args;

	for (; ;) {
		if (fifo->in != fifo->out) {
			kfifo_get(fifo, buf, sizeof(buf));
			fprintf(stdout, "buf:%s\n", buf);
			bzero(buf, sizeof(buf));
		}
		sleep(1);
	}
}

static void kfifo_test()
{
	uint8_t i;
	pthread_t pids[10];

	struct kfifo *kfifo;
	pthread_mutex_t lock;

	pthread_mutex_init(&lock, NULL);
	kfifo = kfifo_alloc(0x100000, &lock);
	for (i = 0; i < sizeof(pids)/sizeof(pthread_t); i++) {
		if (i < 5)
			pthread_create(&pids[i], NULL, rroutine, (void *)kfifo);
		else
			pthread_create(&pids[i], NULL, wroutine, (void *)kfifo);
	}
	for (i = 0; i < sizeof(pids)/sizeof(pthread_t); i++)
		pthread_join(pids[i], NULL);
}

int main(int argc, char *argv[])
{
    int i;
    if (argc != 2) {
        Logd("./main count\n");
        exit(EXIT_FAILURE);
    }
    int scores[] = {1, 10, 666, 23, 890, 172};
    signal(SIGUSR1, signal_handler);
    listTest(atoi(argv[1]));
    hlistTest(atoi(argv[1]));
	hlistTest1(atoi(argv[1]));
    Logd("second=%d\n", findSecondMax(scores, sizeof(scores)/sizeof(int)));
    int arr[] = {12, 1234, 89, 9, 1223, 78, 1237, 5663, 902, 100, 154};
    sort(arr, sizeof(arr)/sizeof(int));
    for (i = 0; i < (int)(sizeof(arr)/sizeof(int)); i++) {
      printf("%d ", arr[i]);
    }
    putchar('\n');
    printf("index=%d\n", binary_search(arr, sizeof(arr)/sizeof(int), 90));
    printf("index=%d\n", binsearch(arr, 0, sizeof(arr)/sizeof(int) - 1, 902));
	kfifo_test();
	getchar();
    return 0;
}
