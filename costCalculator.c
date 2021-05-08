
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


#define NUM_CONSUMERS 1


/**
 * Entry point
 * @param argc
 * @param argv
 * @return
 */
pthread_mutex_t m;
pthread_cond_t cond1, cond2;
queue *q;

void* producer(void* array){
    //start critical section. Locks shared memory
    pthread_mutex_lock(&m);
    //while the queue is full producer waits until consumer liberates one space in the queue
    while (queue_full(q)){
        pthread_cond_wait(&cond1, &m);
    }
    //taking the time and type from the array and inserting into element
    int *row_instruction = (int *) array;
    element * elem = malloc(sizeof(elem));
    elem ->time = row_instruction[1];
    elem ->type = row_instruction[2];
    //inserting in the queue the element
    queue_put(q, elem);
    // sending signal to the consumer to say it has finished
    pthread_cond_signal(&cond2);
    //unlocking critical section
    pthread_mutex_unlock(&m);
}

void* consumer(void *arg){
    int num_lines = (int)arg;
    int total, i;
    //the consumer must read all lines
    for (i = 0; i < num_lines; i++){
        //start critical section. Locks shared memory
        pthread_mutex_lock(&m);
        //While the queue is empty, the consumer waits until the producer introduce a production in the queue
        while (queue_empty(q)){
            //waits until it receives the signal of the producer
            pthread_cond_wait(&cond2, &m);
        }
        //creating an element to get the element of the queue and adding it to the sum
        element *prize;
        cost = (element*)malloc(sizeof(element));
        cost = queue_get(q);
        int time;
        int type;
        time = cost -> time;
        type = cost -> type;
        total = total + (time * type);
        //sending the signal to the producer, because it has finnished
        pthread_cond_broadcast(&cond1);
        //unlocking the mutex
        pthread_mutex_unlock(&m);
    }
    //return the total cost
    return &total;
}

int main (int argc, const char * argv[]) {
    int total = 0;
    int i, num_lines,j;
    FILE *fd;
    //Obtaining number of producers
    int num_producers = atoi(argv[2]);
    //Initializing threads, mutex and conditions
    pthread_t producerth[num_producers];
    pthread_t consumerth;
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cond1, NULL);
    pthread_cond_init(&cond2, NULL);
    // opening the file where instructions are written
    //if error returns an error message
    if ((fd = fopen(argv[1], O_RDONLY)) < 0){
        perror("Error opening the file");
    }
    // taking the number of instructions to be read
    fscanf(fd, "%d", &num_lines);
    //array of three positions, where instructions will be stored.
    //1º position: id of instruction, 2º position: cost of instruction, 3º position: time of use
    int array[num_lines][3];
    //loop iterating through the instructions
    for (i = 0; i < num_lines; i++){
        fscanf(fd, "%d %d %d", &array[i][0], &array[i][1], &array[i][2]);
    }
    //creating thread for the consumer
    if ((pthread_create(&consumerth, NULL, consumer, &num_lines)) < 0){
        perror ("Error creating thread\n");
    };
    //creating threads for the instructions and spliting them into the producers
    for (j=0; j < num_lines; j = j + num_producers){
        for (i=0; i< num_producers; i++){
            if (j+i < num_lines){
                if ((pthread_create(&producerth[i], NULL, producer, array[j + i])) < 0){
                    perror("Error creating thread\n");
                }
            }
        }
    }
    pthread_join(consumerth, (void *)total);
    printf("Total: %d €.\n", **total);
    //destroying mutex and conditionals
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
    return 0;
}
