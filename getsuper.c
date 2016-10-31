#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "showsuper.h"

struct minix_super_block* getSuperBlock(int fd)
{
    struct minix_super_block *superblock = malloc(sizeof(struct minix_super_block));
    lseek(fd,1024,SEEK_SET);
    read(fd, superblock, 1024);
    return superblock;
} 
