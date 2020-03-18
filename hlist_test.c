#include <string.h>
#include <strings.h>

#include "list.h"

#define __STR(a) #a

#define __CNUM(a, b, c) a##b##c
#define __SNUM(a, b, c) a##b##c
#define STR(a,b,c) a##b##c

typedef struct tsPersonId {
	int age;
	char name[32];
	struct hlist_node node;
} tsPersonId;

static struct hlist_head *call_hash(struct hlist_head *hash, int size, int id)
{
	return &hash[id % size];
}

int main(int argc, char **argv)
{
	int i;
	tsPersonId *person;
	struct hlist_head *hash, *temp;
	const char *names[] = {
		"joker",
		"jordan",
		"kobe",
		"lebron",
		"wade",
		"paul",
		"tracy",
		"iverson"
	};
	if (argc < 3) return -1;
	hash = malloc(atoi(argv[1]) * sizeof(hash));
	if (!hash)
		return -1;

	/* init hlist head */
	for (i = 0; i < atoi(argv[1]); i++) {
		INIT_HLIST_HEAD(&hash[i]);
	}

	/* add data to hash map */
	for (i = 0; i < atoi(argv[2]); i++) {
		person = malloc(sizeof(*person));
		if (person) {
			bzero(person, sizeof(*person));
			person->age = i;
			memcpy(person->name, names[random()%(sizeof(names)/sizeof(names[0]))], sizeof(person->name));
			INIT_HLIST_NODE(&person->node);
			temp = call_hash(hash, atoi(argv[1]), person->age);
			hlist_add_head(&person->node, temp);
		}
	}
	tsPersonId *ps;
	struct hlist_node *pos, *n;
	for (i = 0; i < atoi(argv[1]); i++) {
		fprintf(stdout, "----------------------------------------------hash_table_%d----------------------------------------------\n",i);
		hlist_for_each_entry_safe(ps, pos, n, &hash[i], node) {
			fprintf(stdout, "age=%d	name=%s\n", ps->age, ps->name);
		}
	}
	fprintf(stdout, "%s\n", __STR(abcdefghi));
	fprintf(stdout, "%d\n", __CNUM(1,2,3));
	/* free hash table */
	for (i = 0; i < atoi(argv[1]); i++) {
		hlist_for_each_entry_safe(ps, pos, n, &hash[i], node) {
			hlist_del(&ps->node);
			free(ps);
		}
	}
	return 0;
}
