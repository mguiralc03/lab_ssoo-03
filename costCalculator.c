
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/stat.h>
#include <pthread.h>
#include "queue.h"
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
int total_cost;

void* producer(void* array){
    //start critical section. Locks shared memory
    if (pthread_mutex_lock(&m));
    //while the queue is full producer waits until consumer liberates one space in the queue
    while (queue_full(q)){
        pthread_cond_wait(&cond1, &m);
    }
    //taking the time and type from the array and inserting into element
    int *row_instruction = (int *) array;
    element * elem = malloc(sizeof(elem));
    elem ->time = row_instruction[2];
    elem ->type = row_instruction[1];
    //inserting in the queue the element
    queue_put(q, elem);
    // sending signal to the consumer to say it has finished
    pthread_cond_signal(&cond2);
    //unlocking critical section
    pthread_mutex_unlock(&m);
    pthread_exit(NULL);
}

void* consumer(void *arg){
    int *num_lines = (int *)arg;
    int i, time, type;
    int cost[3] = {1,3,10};
    //the consumer must read all lines
    for (i = 0; i < *num_lines; i++){
        //start critical section. Locks shared memory
        pthread_mutex_lock(&m);
        //While the queue is empty, the consumer waits until the producer introduce a production in the queue
        while (queue_empty(q)){
            //waits until it receives the signal of the producer
            pthread_cond_wait(&cond2, &m);
        }
        //creating an element to get the element of the queue and adding it to the sum
        element *operation;
        operation = (element*)malloc(sizeof(element));
        operation = queue_get(q);
        time = operation -> time;
        type = operation -> type;
        total_cost = total_cost + (time * cost[type -1]);
        //sending the signal to the producer, because it has finnished
        pthread_cond_broadcast(&cond1);
        //unlocking the mutex
        pthread_mutex_unlock(&m);
    }
    //return the total cost
    pthread_exit(&total_cost);
}

int main (int argc, const char * argv[]) {
    if (argc == 4 && atoi(argv[2]) > 0 && atoi(argv[3]) > 0){
        void *total;
        int i, num_lines,j;
        FILE *fd;
        //Obtaining number of producers
        int num_producers = atoi(argv[2]);
        //Initializing threads, mutex and conditions
        pthread_t producerth[num_producers];
        pthread_t consumerth;
        if ((pthread_mutex_init(&m, NULL)) != 0){
            perror("Error at initializing the mutex");
        }
        if ((pthread_cond_init(&cond1, NULL)) != 0){
            perror("Error at initializing the first condition variable");
        }
        if ((pthread_cond_init(&cond2, NULL)) != 0){
            perror("Error at initializing the first condition variable");
        }
        q = queue_init(atoi(argv[3]));
        // opening the file where instructions are written
        //if error returns an error message
        if (!(fd = fopen(argv[1], "r"))){
            perror("Error opening the file");
            return -1;
        }
        // taking the number of instructions to be read
        fscanf(fd, "%d", &num_lines);
        if (num_lines <= 0){
            perror("The number of lines must be greater than 0");
            return -1;
        }
        //array of three positions, where instructions will be stored.
        //1?? position: id of instruction, 2?? position: cost of instruction, 3?? position: time of use
        int array[num_lines][3];
        //loop iterating through the instructions
        for (i = 0; i < num_lines; i++){
            fscanf(fd, "%d %d %d", &array[i][0], &array[i][1], &array[i][2]);
            //The first position of the array is the id, which is always equal to the current iteration + 1
            //We use this to detect when fscanf is reading outside the file because num_lines is greater than
            //the number of lines in the file
            if (array[i][0] != i+1){
                printf("The number of lines is greater than the number of rows in the file.\n");
                return -1;
            }
        }
        //creating thread for the consumer
        if ((pthread_create(&consumerth, NULL, consumer, &num_lines)) < 0){
            perror ("Error creating thread");
        };
        //creating threads for the instructions and spliting them into the producers
        for (j=0; j < num_lines; j = j + num_producers){
            for (i=0; i< num_producers; i++){
                if (j+i < num_lines){
                    if ((pthread_create(&producerth[i], NULL, producer, array[j + i])) < 0){
                        perror("Error creating thread");
                    }
                    if (pthread_join(producerth[i], NULL) < 0)
                        return -1;
                }
            }
        }
        if (pthread_join(consumerth, &total) < 0)
            return -1;
        printf("Total: %d ???.\n", *(int *)total);
        //destroying mutex and conditionals
        queue_destroy(q);
        fclose(fd);
        if(pthread_mutex_destroy(&m) != 0)
            perror("Error destroying mutex");
        if(pthread_cond_destroy(&cond1) != 0)
            perror("Error destroying condition 1");
        if(pthread_cond_destroy(&cond2) != 0)
            perror("Error destroying condition 2");
        return 0;
    }
    printf("Incorrect arguments: Must be three, one file and two integers greater than 0\n");
    return -1;
}
