#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "traverse.h"
#include "showsuper.h"
#include "getsuper.h"

//TODO: get to work with the -l flag
void traverse(int fd) {

    //Find the necessary information from the super block
    struct minix_super_block *superBlock = getSuperBlock(fd);
    //find the root node
    lseek(fd, 4 * 1024, SEEK_SET);
    struct minix_inode rootNode;
    read(fd, &rootNode, sizeof(struct minix_inode));

    //go through all dir entries of the root directory and print the name

        //All of the zones appear to be the same because looping through them produced the same result.
        //Because of this we only use the first zone
        long address = (rootNode.i_zone[0] + superBlock->s_firstdatazone) * 1024;
        lseek(fd, address, SEEK_SET);

        for (int entryAddress = 0; entryAddress < 1024; entryAddress += 16) {
            struct minix_dir_entry entry;
            read(fd, &entry, 16);

            //This takes care not to print blank lines
            if (strcmp(entry.name, "")) {
                for (int i = 0; i < 16; i++) {
                    printf("%c", entry.name[i]);
                }

                printf("\n");
            }
        }
}