#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "queue.h"


//To create a queue
queue* queue_init(int capacity){
    //Initializing all parameters in the queue
    queue *q = (queue *)malloc(sizeof(queue));
    int num;
    num = sizeof(element) * capacity;
    q -> array[num];
    q -> capacity = capacity;
    q -> size = 0;
    q -> front = malloc(sizeof(element));
    q -> rear = malloc(sizeof(element));
    //returning the queue
    return q;
}


// To Enqueue an element
int queue_put(queue *q, element *x) {
    //waiting until the queue has a empty space
    while(queue_full(q) == 1){}
    //printf("before if\n");
    //when the queue has an empty space it checks if the queue was empty
    if (queue_empty(q)){
        //printf("after if\n");
        //if the queue is empty the new element is going to be set as the front element
        (q -> front) = *x;
        //element *a;
        //a = &(q -> front);
        //printf("%d\n", a->time);
    }
    // if the queue is not empty nor full, we put the new element as the last one
    q -> array[q -> size] = *x;
    q -> size++;
    q -> rear = *x;
    return 0;
}


// To Dequeue an element.
element* queue_get(queue *q) {
    //waiting until the queue has an element
    while(queue_empty(q)){}
    //when the queue has an element it returns the front one
    element *ele;
    int i;
    ele = &(q -> front);
    //displacing the elements one position to the front of the queue
    for (i = 1; i < (q -> size); i++){
        q -> array[i-1] = q -> array[i];
    }
    //size decrease by one
    q -> size--;
    //declaring the new front
    q -> front = q -> array[0];
    //declaring the new rear
    q -> rear = q -> array[q -> size - 1];
    return ele;
}


//To check queue state
int queue_empty(queue *q){
    //if the size is zero the queue is empty, return 1
    //else return 0
    return (q -> size == 0);
}

int queue_full(queue *q){
    // if the size is equal to the capacity the queue is full, return 1
    // else return 0
    return (q -> size == q -> capacity);
}

//To destroy the queue and free the resources
int queue_destroy(queue *q){
  // liberating the memory of the array and the queue
    free(q -> array);
    free(q);
    return 0;
}
