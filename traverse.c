#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "traverse.h"
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
    struct minix_super_block *superBlock = getSuperBlock(fd);

    //find the root node
    lseek(fd,4*1024,SEEK_SET);
    struct minix_inode *rootNode = malloc(sizeof(struct minix_inode));
    read(fd,rootNode,sizeof(struct minix_inode));

    //go through all dirents of the root directory and print the name
    for(short zone = 0;zone<7;zone++)
    {
        long address = (rootNode->i_zone[zone] + -1 + superBlock->s_firstdatazone) * 1024;
        printf("%d\n",address);
        lseek(fd,address,SEEK_SET);

        //TODO:This loop appears to not print off the proper stuff but not sure where the problem is
        for(int entryAddress = 0;entryAddress<1024;entryAddress+= sizeof(struct minix_dir_entry))
        {
            printf("flag1\n");
            struct minix_dir_entry *entry = malloc(sizeof(struct minix_dir_entry));
            read(fd,entry,sizeof(struct minix_dir_entry));
            printf("flag2\n");
            printf("%s\n",*(entry->name));
        }
    }
}