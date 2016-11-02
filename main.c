#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "help.h"
#include "showsuper.h"
#include "traverse.h"

void main() {
    char *exit = "exit";
    char *cmd;
    char *mnt;
    int fd;

    //TODO: Don't allow the uer to use commands that require a fd until an image is mounted
    //TODO: entering nothing and hitting enter causes a segmentation fault
    while (1) {

        printf("minix: ");
        char input[100];
        fgets(input, 99, stdin);
        cmd = strtok(input, "\n ");

        if (strcmp(cmd, "quit") == 0) {
            break;
        } else if (strcmp(cmd, "help") == 0) {
            help();
        } else if (strcmp(cmd, "minimount") == 0) {
            mnt = strtok(NULL, "\n ");
            if (mnt == NULL) {
                printf("Please enter file name after minimount\n(eg:minimount imagefile.img)\n");
            }
            fd = open(mnt, O_RDONLY);
            if (fd == -1) {
                printf("Not a valid file name\n");
            }
        } else if (strcmp(cmd, "miniumount") == 0) {

        } else if (strcmp(cmd, "showsuper") == 0) {
            showsuper(fd);
        } else if (strcmp(cmd, "traverse") == 0) {
            mnt = strtok(NULL, "\n ");
            if (mnt == NULL) {
                traverse(fd, 0);
            } else if (strcmp(mnt, "-l") == 0) {
                traverse(fd, 1);
            } else {
                printf("Please enter a valid command\n");
            }
        } else if (strcmp(cmd, "showzone") == 0) {
            printf("success for showzone\n");
        } else if (strcmp(cmd, "showfile") == 0) {
            printf("success for showfile\n");
        } else {
            printf("Please enter a valid command\n");
        }


    }

}
