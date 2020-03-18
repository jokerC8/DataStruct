#ifndef __HLIST_H_
#define __HLIST_H_

#include <stdio.h>

#define LIST_POISON1 ((void *) 0x00100100)
#define LIST_POISON2 ((void *) 0x00200200)

/* preload, leave empty here */
static inline void prefetch(const void *x) {;}
static inline void prefetchw(const void *x) {;}

#define offsetof(TYPE, MEMBER) (size_t)(&(((TYPE *)0)->MEMBER))

#define container_of(ptr, type, member) ({ \
		const typeof(*ptr) *__ptr = ptr; \
		(type *)((char *)__ptr - offsetof(type, member));})

struct hlist_node {
	struct hlist_node *next;
	struct hlist_node **pprev;
};

struct hlist_head {
	struct hlist_node *first;
};

#define HLIST_HEAD_INIT {.first = NULL}

#define HLIST_HEAD(head) struct hlist_head head = HLIST_HEAD_INIT

#define INIT_HLIST_HEAD(head) ((head)->first = NULL)

#define INIT_HLIST_NODE(node) ((node)->next = NULL, (node)->pprev = NULL)

static inline int hlist_unhashed(struct hlist_node *node)
{
	return !node->pprev;
}

static inline int hlist_empty(struct hlist_head *head)
{
	return !head->first;
}

static inline void __hlist_del(struct hlist_node *node)
{
	*node->pprev = node->next;
	if (node->next)
		node->next->pprev = node->pprev;
}

static inline void hlist_del(struct hlist_node *node)
{
	__hlist_del(node);
	node->next = LIST_POISON1;
	node->pprev = LIST_POISON2;
}

static inline void hlist_del_init(struct hlist_node *node)
{
	__hlist_del(node);
	INIT_HLIST_NODE(node);
}

static inline void hlist_add_head(struct hlist_head *head, struct hlist_node *node)
{
	struct hlist_node *first;

	first = head->first;
	head->first = node;
	node->pprev = &head->first;
	node->next = first;

	if (first) 
		first->pprev = &node->next;
}

static inline void hlist_add_before(struct hlist_node *node, struct hlist_node *next)
{
	*next->pprev = node;
	node->pprev = next->pprev;
	node->next = next;
	next->pprev = &node->next;
}

static inline void hlist_add_after(struct hlist_node *node, struct hlist_node *next)
{
	struct hlist_node *after;

	after = next->next;
	next->next = node;
	node->pprev = &next->next;
	node->next = after;

	if (after)
		after->pprev = &node->next;
}

#define hlist_entry(ptr, type, member) container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
	for (pos = (head)->first;\
		 pos && ({prefetch(pos->next); 1;});\
		 pos = pos->next) 

#define hlist_for_each_safe(pos, n, head) \
	for (pos = (head)->first;\
		 pos && ({prefetch(pos->next); n = pos->next; 1;});\
		 pos = n)

#define hlist_for_each_entry(tpos, pos, head, list) \
	for (pos = (head)->first;\
		 pos && ({prefetch(pos->next); tpos = hlist_entry(pos, typeof(*tpos), list); 1;});\
		 pos = pos->next)

#endif
