#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include "traverse.h"
#include "showsuper.h"
#include "getsuper.h"

//TODO: get to work with the -l flag
void traverse(int fd, int detailPrint) {

    //Find the necessary information from the super block
    struct minix_super_block superBlock;
    getSuperBlock(fd,&superBlock);
    //find the root node
    lseek(fd, 4 * 1024, SEEK_SET);
    struct minix_inode rootNode;
    read(fd, &rootNode, sizeof(struct minix_inode));

    //go through all dir entries of the root directory and print the name

    //All of the zones appear to be the same because looping through them produced the same result.
    //Because of this we only use the first zone
    long address = (rootNode.i_zone[0] + superBlock.s_firstdatazone) * 1024;
    lseek(fd, address, SEEK_SET);

    for (int entryAddress = 0; entryAddress < 1024-16; entryAddress += 16) {
        struct minix_dir_entry entry;
        read(fd, &entry, 16);

        //This takes care not to print blank lines
        if (strcmp(entry.name, "")) {

            if (detailPrint) {
                lseek(fd, (superBlock.s_zmap_blocks+superBlock.s_imap_blocks+2) * 1024, SEEK_SET);
                lseek(fd, ((entry.inode-1) * 32), SEEK_CUR);
                struct minix_inode node;
                read(fd, &node, 32);

                //Print off mode
                short mode = node.i_mode;
                short directory_MASK = 0x4000;
                short mr1 = 0x0100; //mr1 means mask read group one in - (r)wx rwx rwx
                short mw1 = 0x0080; //the rest of these names follow the syle of the above
                short mx1 = 0x0040;
                short mr2 = 0x0020;
                short mw2 = 0x0010;
                short mx2 = 0x0008;
                short mr3 = 0x0004;
                short mw3 = 0x0002;
                short mx3 = 0x0001;


                //directory or file
                if((mode&directory_MASK) > 0)
                {
                    printf("d");
                }
                else
                {
                    printf("-");
                }

                (mode&mr1)>0 ? printf("r") : printf("-");
                (mode&mw1)>0 ? printf("w") : printf("-");
                (mode&mx1)>0 ? printf("x") : printf("-");
                (mode&mr1)>0 ? printf("r") : printf("-");
                (mode&mw2)>0 ? printf("w") : printf("-");
                (mode&mx2)>0 ? printf("x") : printf("-");
                (mode&mr3)>0 ? printf("r") : printf("-");
                (mode&mw3)>0 ? printf("w") : printf("-");
                (mode&mx3)>0 ? printf("x") : printf("-");

                printf(" %d ", node.i_uid);
                printf("%d ", node.i_size);
                if(node.i_size<1000 ) //helps with spacing
                {
                    printf(" ");
                }

                struct tm *info;
                info = localtime( &node.i_time );

                if(info->tm_mon==0) printf("Jan ");
                if(info->tm_mon==1) printf("Feb ");
                if(info->tm_mon==2) printf("Mar ");
                if(info->tm_mon==3) printf("Apr ");
                if(info->tm_mon==4) printf("May ");
                if(info->tm_mon==5) printf("Jun ");
                if(info->tm_mon==6) printf("Jul ");
                if(info->tm_mon==7) printf("Aug ");
                if(info->tm_mon==8) printf("Sep ");
                if(info->tm_mon==9) printf("Oct ");
                if(info->tm_mon==10) printf("Nov ");
                if(info->tm_mon==11) printf("Dec ");

                printf("%d ",info->tm_mday);

                //I don't think this year is right
                printf("%d ",info->tm_year);

                lseek(fd,address+entryAddress+16,SEEK_SET);
            }

            for (int i = 0; i < 14; i++) {
                printf("%c", entry.name[i]);
            }
            printf("\n");
        }
    }
}