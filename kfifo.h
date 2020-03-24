#ifndef __KFIFO_H_
#define __KFIFO_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>

#define is_pow_of_two(n) !((n) & (n - 1))

#define min(n, m) ((n) < (m) ? (n) : (m))

struct kfifo {
	unsigned char *buffer;
	unsigned int size;
	unsigned int in;
	unsigned int out;
	pthread_mutex_t *lock;
};

static inline unsigned int roundup_pow_of_two(unsigned int size)
{
	unsigned int n = 1UL;

	if (1 == size)
		return size;
	while (n < size) {
		n <<= 1;
	}

	return n;
}

static inline struct kfifo *kfifo_init(unsigned char *buffer, unsigned int size, pthread_mutex_t *lock)
{
	struct kfifo *fifo;

	assert(is_pow_of_two(size));
	fifo = malloc(sizeof(*fifo));
	if (!fifo) return NULL;
	fifo->buffer = buffer;
	fifo->size = size;
	fifo->lock = lock;
	fifo->in = fifo->out = 0;

	return fifo;
}

static inline struct kfifo *kfifo_alloc(unsigned int size, pthread_mutex_t *lock)
{
	unsigned char *buffer;
	struct kfifo *fifo;

	if (!is_pow_of_two(size)) {
		size = roundup_pow_of_two(size);
	}
	buffer = malloc(size);
	if (!buffer) return NULL;
	fifo = kfifo_init(buffer, size, lock);
	return fifo;
}

static inline unsigned int __kfifo_put(struct kfifo *fifo, unsigned char *buffer, unsigned int n)
{
	unsigned int len, l;

	/* calculating space avaliable */
	len = min(n, fifo->size - fifo->in + fifo->out);

	l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));

	memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, l);

	memcpy(fifo->buffer, buffer + l, len - l);

	fifo->in += len;
	return len;
}

static inline unsigned int __kfifo_get(struct kfifo *fifo, unsigned char *buffer, unsigned int n)
{
	unsigned int len, l;

	len = min(n, fifo->in - fifo->out);

	l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));

	memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), l);

	memcpy(buffer + l, fifo->buffer, len - l);

	fifo->out += len;
	return len;
}

static inline unsigned int kfifo_put(struct kfifo *fifo, unsigned char *buffer, unsigned int size)
{
	unsigned int n;

	pthread_mutex_lock(fifo->lock);
	n = __kfifo_put(fifo, buffer, size);
	pthread_mutex_unlock(fifo->lock);

	return n;
}

static inline unsigned int kfifo_get(struct kfifo *fifo, unsigned char *buffer, unsigned int size)
{
	unsigned int n;

	pthread_mutex_lock(fifo->lock);
	n = __kfifo_get(fifo, buffer, size);
	if (fifo->in == fifo->out)
		fifo->in = fifo->out = 0;
	pthread_mutex_unlock(fifo->lock);

	return n;
}

static inline unsigned int kfifo_len(struct kfifo *fifo)
{
	unsigned int len;

	pthread_mutex_lock(fifo->lock);
	len = fifo->in - fifo->out;
	pthread_mutex_unlock(fifo->lock);

	return len;
}
#endif
