/* Filename: select_with_fd_client.c */
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "file_descriptor.h"

int main() {
    // int fileDescriptor1;
    int fileDescriptor1, fileDescriptor2;
    
    fileDescriptor1 = open(FIFO_FILE_A, O_CREAT|O_WRONLY);
    fileDescriptor2 = open(FIFO_FILE_B, O_CREAT|O_WRONLY);

    char readbuf[256];
    int end_process;
    int stringlen;
    char end_str[5];
    strcpy(end_str, "end");
    printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");

    int fd_index = 0;
    while(true) {
        printf("Enter string: ");
        fgets(readbuf, sizeof(readbuf), stdin);
        stringlen = strlen(readbuf);
        readbuf[stringlen - 1] = '\0';
        end_process = strcmp(readbuf, end_str);

        if (fd_index %2 == 0) {
            write(fileDescriptor1, readbuf, strlen(readbuf));
            printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
        } else {
            write(fileDescriptor2, readbuf, strlen(readbuf));
            printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
        }

        if (end_process == 0) {
            close(fileDescriptor1);
            close(fileDescriptor2);

            break;
        }
    }

    return 0;
}