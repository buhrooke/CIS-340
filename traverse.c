#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "showsuper.h"

int numberOfInodes = -1;

void main()
{
    //Open up the image file
    //TODO: Replace this by passing in a file descriptor from custom minix terminal
    char *imageLoaction = malloc(sizeof(char)*100);
    printf("Minix Image Location: ");
    scanf("%s", imageLoaction);

    int fd = open(imageLoaction, O_RDONLY);
    if(fd == -1)
    {
        printf("Error can't find image file\n");
        exit(-1);
    }
    free(imageLoaction);

    numberOfInodes = getSuperBlock(fd)->s_ninodes;
    printf("Number of INodes %d\n", numberOfInodes);
}