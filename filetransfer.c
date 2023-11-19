//server.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 7891
#define MAX_BUFFER_SIZE 1024
#define FILENAME "sample.txt"

int main() {
    int udpSocket;
    FILE *file;
    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;

   
    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    
    bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    printf("Server listening on port %d...\n", PORT);

    addr_size = sizeof clientAddr;

    recvfrom(udpSocket, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &clientAddr, &addr_size);

    file = fopen(FILENAME, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    printf("/nFile content:\n");
    while (fread(buffer, 1, sizeof(buffer), file) > 0) {
        printf("%s", buffer); // Print content
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer
    }
    printf("\n");

    rewind(file);

    while (fread(buffer, 1, sizeof(buffer), file) > 0) {
        sendto(udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr *) &clientAddr, addr_size);
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer
    }

    strcpy(buffer, "EOF");
    sendto(udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr *) &clientAddr, addr_size);

    fclose(file);
    close(udpSocket);

    printf("File received successfully!\n");

    return 0;
}

//client.c


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 7891
#define SERVER_IP "127.0.0.1"
#define MAX_BUFFER_SIZE 1024

int main() {
    int udpSocket;
    FILE *file;
    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in serverAddr;

    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    printf("Enter the filename: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    sendto(udpSocket, buffer, strlen(buffer), 0, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    file = fopen("received_file.txt", "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    while (1) {
        recvfrom(udpSocket, buffer, MAX_BUFFER_SIZE, 0, NULL, NULL);

        if (strcmp(buffer, "EOF") == 0) {
            // End of file transfer
            break;
        }

        fwrite(buffer, 1, sizeof(buffer), file);
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer
    }

    fclose(file);
    close(udpSocket);

    printf("File send successfully!\n");

    return 0;
}








