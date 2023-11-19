//server.c

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<unistd.h>


int main() {
    int welcomeSocket, newSocket;
    char buffer[1024] = "Hello Humans\n";
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;

    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    listen(welcomeSocket, 5);
    printf("Listening...\n");

    addr_size = sizeof(clientAddr);
    newSocket = accept(welcomeSocket, (struct sockaddr *) &clientAddr, &addr_size);

    send(newSocket, buffer, strlen(buffer), 0);

    close(newSocket);
    close(welcomeSocket);
    return 0;
}

//client.c

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    addr_size = sizeof(serverAddr);
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    recv(clientSocket, buffer, sizeof(buffer), 0);

    printf("Data received: %s", buffer);

    close(clientSocket);
    return 0;
}









