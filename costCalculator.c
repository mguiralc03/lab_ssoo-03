
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

int producer(int id, int machine_type, int time_of_use){
    //Write in the queue
}

int consumer(){
    //read from the queue
}

int main (int argc, const char * argv[] ) {
    int total = 0;
    int i, *fd, num_lines;
    close(STDIN_FILENO);
    if ((*fd = open(argv[1], O_RDONLY)) < 0){
        perror("Error opening the file");
    }
    fscanf(fd, "%d", &num_lines);
    int array[num_lines][3];
    for (i = 0; i < num_lines; i++){
        fscanf(fd, "%d %d %d", array[i][0], array[i][1], array[i][2]);
    }
    printf("Total: %i €.\n", total);

    return 0;
}
