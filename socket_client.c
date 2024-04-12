#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    char message[1024];
    char *end_str = "end";
    char *bye_str = "bye";
    printf("socket_client: Send messages, infinitely, to end enter \"end\"\n");
    while(1) {
        printf("Enter string: ");
        fgets(message, sizeof(message), stdin);
        message[strlen(message) - 1] = '\0';

        send(sock, message, strlen(message), 0);
        printf("socket_client: Message(%s) sent\n", message);

        memset(buffer, 0, 1024);
        valread = read(sock, buffer, 1024);
        printf("socket_client: Received(%s) of length(%d).\n", buffer, valread);

        if (strcmp(message, end_str) == 0 || strcmp(buffer, bye_str) == 0) {
            break;
        }
    }
    
    return 0;
}
