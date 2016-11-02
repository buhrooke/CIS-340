#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "showsuper.h"
#include "getsuper.h"

void getSuperBlock(int fd, struct minix_super_block *superblock)
{
    lseek(fd,1024,SEEK_SET);
    read(fd, superblock, sizeof(struct minix_super_block));
} 
