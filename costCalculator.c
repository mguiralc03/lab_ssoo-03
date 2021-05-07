
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

void* producer(void* array){
    //Write in the queue
}

void* consumer(){
    //read from the queue
}

int main (int argc, const char * argv[]) {
    int total = 0;
    int i, num_lines;
    FILE *fd;
    pthread_t *producerth[argv[2]];
    pthread_t *consumerth;
    pthread_mutex_t m;
    pthread_cond_t *conditions[argv[2]];
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
    //loop iterating thorugh the instructions
    for (i = 0; i < num_lines; i++){
        fscanf(fd, "%d %d %d", &array[i][0], &array[i][1], &array[i][2]);
    }
    pthread_create(&consumerth, NULL, consumer, NULL);
    for (j=0; j < num_lines; j = j + argv[2]){
        for (i=0; i< argv[2]; i++){
            if (j+i < num_lines)
                pthread_create(&producerth[i], NULL, producer, array[j + i])
        }
    }
    for (j=0; j<num_lines; j++){

    }
    printf("Total: %i €.\n", total);

    return 0;
}
