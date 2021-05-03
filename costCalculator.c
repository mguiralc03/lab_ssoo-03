
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
    size_t buffsize = 500;
    char buffer[buffsize];
    int total = 0;
    int i, m;
    close(STDIN_FILENO);
    if ((fd = open(argv[1])) < 0){
        return perror("Error opening the file");
    }
    scanf("%s", buffer);
    //num_bytes = getline(buffer, &buffsize, fd);
    num_lines = atoi(strtok(buffer,"\n"));
    int array[num_lines - 1][3];
    for (i = 0; i < num_lines; i++){
        //lseek(fd, num_bytes, SEEK_CUR);
        //num_bytes = getline(buffer, &buffsize, fd);
        for (m = 0; m < 3; m++){
            array[i][m] =  atoi(strtok(buffer, "\n "));
        }
    }
    printf("Total: %i €.\n", total);

    return 0;
}
