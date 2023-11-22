#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main() {
    // Variable Declarations
    int sd, n, bd, port, clilen;
    char fileread[100], fname[100], rcv[100];
    struct sockaddr_in servaddr, cliaddr;

    printf("Enter the port address: ");
    scanf("%d", &port);

    // Create a socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);

    // Check if the socket is created successfully
    if (sd < 0) {
        printf("Can't create socket\n");
        exit(1);
    } else {
        printf("Socket is created\n");
    }

    // Server Address Setup
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    // Bind the socket to the server address
    bd = bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // Check for successful binding
    if (bd < 0) {
        printf("Can't bind\n");
        exit(1);
    } else {
        printf("Binded\n");
    }

    clilen = sizeof(cliaddr);

    // Receive file name request from the client
    n = recvfrom(sd, rcv, sizeof(rcv), 0, (struct sockaddr *)&cliaddr, &clilen);
    rcv[n] = '\0';

    FILE *fp = fopen(rcv, "r");
    if (fp == NULL) {
        sendto(sd, "error", 5, 0, (struct sockaddr *)&cliaddr, clilen);
    } else {
        while (fgets(fileread, sizeof(fileread), fp)) {
            sendto(sd, fileread, strlen(fileread), 0, (struct sockaddr *)&cliaddr, clilen);
        }
        sendto(sd, "completed", 9, 0, (struct sockaddr *)&cliaddr, clilen);
        fclose(fp);
    }

    close(sd);

    return 0;
}

