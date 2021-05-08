#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/stat.h>
#include <pthread.h>
#include "queue.h"
#include "queue.c"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(){
	int i = 2;
	queue *q;
	q = queue_init(i);
	printf("%d\n", q->size);
	printf("%d\n", q->capacity);
	printf("init done\n");
	printf("%d\n", queue_empty(q));
	printf("%d\n", queue_full(q));
	element *a,*b;
	a = malloc(sizeof(element));
	b = malloc(sizeof(element));
	a->time = 3;
	printf("atime\n");
	a->type = 5;
	b->time = 4;
	b->type = 9;
	printf("numbers introduce\n");
	queue_put(q, a);
	printf("a introduce\n");
	queue_put(q, b);
	printf("b introduce\n");
	element *r;
	r = malloc(sizeof(element));
	r = queue_get(q);
	printf("%d,%d\n", r->type, r->time);
	queue_destroy(q);

}
