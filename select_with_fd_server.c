
/* Filename: select_with_fd_server.c */
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "file_descriptor.h"

int main() {
    printf("create the fifo if it does not exist...\n");
    /* Create the FIFO if it does not exist */
    mknod(FIFO_FILE_A, S_IFIFO|0640, 0);
    mknod(FIFO_FILE_B, S_IFIFO|0640, 0);

    int fileDescriptor1, fileDescriptor2;
    char end_str[5];
    strcpy(end_str, "end");

    printf("server is listening...\n");
    while (true)
    {
        printf("open the file descriptors...\n");
        fileDescriptor1 = open(FIFO_FILE_A, O_RDONLY);
        fileDescriptor2 = open(FIFO_FILE_B, O_RDONLY);

        fd_set fds;
        int maxfd;
        int res;
        char buf[256];
        int to_end_1, to_end_2;

        FD_ZERO(&fds); // Clear FD set for select
        FD_SET(fileDescriptor1, &fds);
        FD_SET(fileDescriptor2, &fds);

        maxfd = fileDescriptor1 > fileDescriptor2 ? fileDescriptor1 : fileDescriptor2;

        printf("select file descriptors...\n");
        int select_ret = select(maxfd + 1, &fds, NULL, NULL, NULL);
        if (select_ret <= 0) {
            printf("select failed, continue...\n");
			continue;
		}

        printf("reset the buf...\n");
        memset(buf, '\0', sizeof(buf));
        if (FD_ISSET(fileDescriptor1, &fds))
        {
            // We can read from fileDescriptor1
            res = read(fileDescriptor1, buf, sizeof(buf));
            if (res > 0)
            {
                printf("Read %d bytes from channel1: %s\n", res, buf);
                to_end_1 = strcmp(buf, end_str);
                if (to_end_1 == 0) {
                    printf("server exit...\n");
                    close(fileDescriptor1);
                    close(fileDescriptor2);
                    break;
                }
            }
        }
        if (FD_ISSET(fileDescriptor2, &fds))
        {
            // We can read from fileDescriptor2
            res = read(fileDescriptor2, buf, sizeof(buf));
            if (res > 0)
            {
                printf("Read %d bytes from channel2:%s\n", res, buf);
                to_end_2 = strcmp(buf, end_str);
                if (to_end_2 == 0) {
                    printf("server exit...\n");
                    close(fileDescriptor1);
                    close(fileDescriptor2);
                    break;
                }
            }
        }
    }

    return 0;
}