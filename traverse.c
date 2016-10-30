#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "showsuper.h"

int numberOfInodes = -1;

//TODO: This should not have a main method. The terminal should call the traverse function
void main()
{
    //Open up the image file
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

    traverse(fd);
}

void traverse(int fd)
{
    //Find the necessary information from the super block
    numberOfInodes = getSuperBlock(fd)->s_ninodes;
    printf("Number of INodes %d\n", numberOfInodes);
}