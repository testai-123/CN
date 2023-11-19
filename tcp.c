#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <unistd.h>


int main() {

	char server_message[256];
	printf("Enter message to sent to client: ");
	scanf("%s",server_message);

	//create the server socket
	int server_socket;
	server_socket = socket(AF_INET,SOCK_STREAM,0);

	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8000);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//bins the socket to specified IP and port
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	//listen to the client sockets
	listen(server_socket,5);

	char buffer[256] = {0};
	int client_socket;
	client_socket = accept(server_socket,NULL,NULL);
	//send the message to client
	send(client_socket,server_message,sizeof(server_message),0);
	
	recv(client_socket,buffer,256,0);
	printf("The client send the response: ");
	printf("%s\n",buffer);
	// close the socket
	close(server_socket);
	return 0;
}

//client

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <unistd.h>

int main() {
	// create a socket
	int network_socket;
	network_socket = socket(AF_INET,SOCK_STREAM,0);

	// specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8000);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	// check for error while connection
	if(connection_status == -1)
	{
		printf("Theres was an error in making connection!\n\n");
	}

	// recieve data from the server
	char buffer[256] = {0};
	recv(network_socket,&buffer,sizeof(buffer),0);

	printf("The server send the response: %s\n",buffer);
	
	char message[256];
	printf("Send message to server: ");
	scanf("%s", message);
	send(network_socket,message,strlen(message),0);
	
	close(network_socket);
	return 0;
}
