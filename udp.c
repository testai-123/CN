#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include <unistd.h>

#define MAX 1024
#define PORT 8080

int main() {
	int server_socket;
	char buffer[MAX];
	char hello[256];
	
	// creation of server socket
	server_socket = socket(AF_INET,SOCK_DGRAM,0);
	if(server_socket < 0)
	{
		perror("Error in creating socket!");
		exit(EXIT_FAILURE);
	}
	
	//set memory for the client socket address
	struct sockaddr_in client_adddress;
	memset(&client_adddress,0,sizeof(client_adddress));
	
	// specify address of server socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	// bind the server socket with the available client socket
	bind(server_socket,(const struct sockaddr *)&server_address,sizeof(server_address));
	
	int n;
	socklen_t len;
	len = sizeof(client_adddress);
	
	// recvfrom recieves the hello message from socket
	n = recvfrom(server_socket,(char *)buffer,MAX,MSG_WAITALL,(struct sockaddr *)&client_adddress,&len);
	buffer[n] = '\0';
	printf("Client: %s\n",buffer);
	printf("\nEnter message: ");
	scanf("%s", hello);
	sendto(server_socket,(char *)hello,strlen(hello),MSG_CONFIRM,(const struct sockaddr *)&client_adddress,sizeof(client_adddress));
	printf("\nMessage Sent to client\n");
	close(server_socket);
	return 0;
}

//client

#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include <unistd.h>
#include <string.h>


#define MAX 1024
#define PORT 8080
int main() {
	
	int network_socket;
	char buffer[MAX];
	char hello[256];
	
	// creation of client socket
	network_socket = socket(AF_INET,SOCK_DGRAM,0);
	if(network_socket < 0)
	{
		perror("Socket creation failed!");
		exit(EXIT_FAILURE);
	}
	
	// define server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	int n;
	socklen_t len;
	printf("\nEnter message: ");
	scanf("%s", hello);
	// sendto function in UDP sends the hello message to server
	sendto(network_socket,(char *)hello,strlen(hello),MSG_CONFIRM,(const struct sockaddr *)&server_address, sizeof(server_address));
	
	printf("Message sent to server!");
	
	len = sizeof(server_address);
	
	// recvfrom recieves the message from server
	n = recvfrom(network_socket,buffer,MAX,MSG_WAITALL,(struct sockaddr *)&server_address, &len);
	
	buffer[n] = '\0';
	printf("\nServer: %s\n",buffer);
	
	close(network_socket);
	return 0;
	}
