#ifndef HEADER_FILE
#define HEADER_FILE


typedef struct element {
  int type; //Machine type
  int time; //Using time
}element;

typedef struct queue {
	// Define the struct yourself
  int size;
  int capacity;
  element *array;
  element front;
  element rear;
}queue;

queue* queue_init (int size);
int queue_destroy (queue *q);
int queue_put (queue *q, element* elem);
element * queue_get(queue *q);
int queue_empty (queue *q);
int queue_full(queue *q);

#endif
