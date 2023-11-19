//server.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
    
    int sockfd;
    char buffer[1024] = "Supp\n";
    struct sockaddr_in serverAddr,client;
    socklen_t len;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    memset(&serverAddr,'\0',sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd,(struct sockaddr *)(&serverAddr),sizeof(serverAddr));

    memset(&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(7891); // Port of the client
    client.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP address of the client

    sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)(&client),sizeof(client));

    close(sockfd);

    return 0;
}

//client.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){

    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t len;

    clientSocket = socket(AF_INET,SOCK_DGRAM,0);

    memset(&serverAddr,'\0',sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(clientSocket,(struct sockaddr *) &serverAddr,sizeof(serverAddr));

    len = sizeof(clientAddr);

    recvfrom(clientSocket,buffer,1024,0,(struct sockaddr *)&clientAddr,&len);
    printf("Data Received : %s",buffer);

    close(clientSocket);
}

