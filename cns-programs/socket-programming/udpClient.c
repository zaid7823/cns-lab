#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main() {
    // Variable Declarations
    int sd, n, cport;
    char name[100], rcvg[100], fname[100];
    struct sockaddr_in servaddr;

    printf("Enter the server port: ");
    scanf("%d", &cport);

    // Create a socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);

    // Check if the socket is created successfully
    if (sd < 0) {
        printf("Error creating socket\n");
        exit(1);
    } else {
        printf("Socket is created\n");
    }

    // Server Address Setup
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Use INADDR_LOOPBACK for local connection
    servaddr.sin_port = htons(cport);

    // Input: File name to request
    printf("Enter the file name to request: ");
    scanf("%s", name);

    sendto(sd, name, strlen(name), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    FILE *fp = fopen("received_file.txt", "w");

    while (1) {
        n = recvfrom(sd, rcvg, 100, 0, NULL, NULL);
        rcvg[n] = '\0';
        if (strcmp(rcvg, "error") == 0) {
            printf("File is not available\n");
            fclose(fp);
            close(sd);
            break;
        }

        if (strcmp(rcvg, "completed") == 0) {
            printf("File is transferred\n");
            fclose(fp);
            close(sd);
            break;
        } else {
            fputs(rcvg, stdout); // Prints the received data to the console
            fprintf(fp, "%s", rcvg); // Writes the received data to the file
        }
    }

    return 0;
}

