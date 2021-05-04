#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "queue.h"



//To create a queue
queue* queue_init(int capacity){
    //Initializing all parameters in the queue
    queue *q = (queue *)malloc(sizeof(queue));
    q -> array = malloc(sizeof(struct element)*capacity);
    q -> capacity = capacity;
    q -> size = 0;
    return q;
}


// To Enqueue an element
int queue_put(queue *q, struct element *x) {
    if (!queue_full(q)){
        if (queue_empty(q))
            q -> front = *x;
        q -> array[q -> size] = *x;
        q -> size++;
        q -> rear = *x;
    }
    return 0;
}


// To Dequeue an element.
struct element* queue_get(queue *q) {
    struct element *element;
    int i;
    element = &(q -> front);
    for (i = 1; i < (q -> size); i++){
        q -> array[i-1] = q -> array[i];
    }
    q -> size--;
    q -> front = q -> array[0];
    q -> rear = q -> array[q -> size - 1];
    //free(q -> array[q -> size]);
    return element;
}


//To check queue state
int queue_empty(queue *q){
    return (q -> size == 0);
}

int queue_full(queue *q){
    return (q -> size == q -> capacity);
}

//To destroy the queue and free the resources
int queue_destroy(queue *q){
    free(q -> array);
    free(q);
    return 0;
}
