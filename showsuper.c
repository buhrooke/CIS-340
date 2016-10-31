#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "showsuper.h"

void showsuper(int fd){
  lseek(fd,1024,SEEK_SET);
  char buffer[1024];
  read(fd, buffer, 1024);
  struct minix_super_block *superblock = (struct minix_super_block *) buffer;
  printf("number of indodes:\t%d\n",superblock->s_ninodes);
  printf("number of zones:\t%d\n",superblock->s_nzones);
  printf("number of imap_blocks:\t%d\n",superblock->s_imap_blocks);
  printf("number of zmap_blocks:\t%d\n",superblock->s_zmap_blocks);
  printf("first data zone:\t%d\n",superblock->s_firstdatazone);
  printf("log zone size:\t\t%d\n",superblock->s_log_zone_size);
  printf("max size:\t\t%d\n",superblock->s_max_size);
  printf("magic:\t\t\t%d\n",superblock->s_magic);
  printf("state:\t\t\t%d\n",superblock->s_state);
  printf("zones:\t\t\t%d\n",superblock->s_zones);




}
