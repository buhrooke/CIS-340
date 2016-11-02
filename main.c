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
    char *zone;
    int zoneNum;
    int fd = NULL;

    //TODO: Don't allow the uer to use commands that require a fd until an image is mounted
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
            if (fd == 0) {
                mnt = strtok(NULL, "\n ");
                if (mnt == NULL) {
                    printf("Please enter file name after minimount\n(eg:minimount imagefile.img)\n");
                } else {
                    fd = open(mnt, O_RDONLY);
                    if (fd == -1) {
                        printf("Not a valid file name\n");
                    }
                }
            } else {
                printf("File already mounted, please unmount current file before mounting another\n");
            }
        } else if (strcmp(cmd, "miniumount") == 0) {
            if (fd == 0) {
                printf("No file currently mounted\n");
            } else {
                close(fd);
                fd = 0;
            }
        } else if (strcmp(cmd, "showsuper") == 0) {
            if (fd == 0) {
                printf("Please mount an image file\n");
            } else {
                showsuper(fd);
            }
        } else if (strcmp(cmd, "traverse") == 0) {
            if (fd == 0) {
                printf("Please mount an image file\n");
            } else {
                mnt = strtok(NULL, "\n ");
                if (mnt == NULL) {
                    traverse(fd, 0);
                } else if (strcmp(mnt, "-l") == 0) {
                    traverse(fd, 1);
                } else {
                    printf("Please enter a valid command");
                }
            }
        } else if (strcmp(cmd, "showzone") == 0) {
            if (fd == 0) {
                printf("Please mount an image file\n");
            } else {
                zone = NULL;
                zone = strtok(NULL, "\n ");
                if (zone == NULL) {
                    printf("Please enter the zone number to display\n");
                } else {
                    zoneNum = atoi(zone);
                    showzone(fd, zoneNum);
                    zoneNum = 0;
                    zone = NULL;
                }
            }
        } else if (strcmp(cmd, "showfile") == 0) {
            if (fd == 0) {
                printf("Please mount an image file\n");
            } else {
                printf("success for showfile\n");
            }
        } else {
            printf("Please enter a valid command\n");
        }
    }

}
