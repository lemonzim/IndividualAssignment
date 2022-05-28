#include <stdio.h>
#include <sys/socket.h>
#include <string.h> // to use strlen
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write
#include <stdlib.h>
#include <sys/socket.h>
int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server; 
	char *message, server_reply[2000];
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	//struct information
	server.sin_addr.s_addr = inet_addr("192.168.56.105");//bind to this ip
	server.sin_family = AF_INET;
	server.sin_port = htons(37);//port37

	//Connect to server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");//output if error
		return 1;
	}
	
	puts("Client wants total seconds from Epoch\n");

	//Send some data
	message ="Date";
	if(send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");//output if error
		return 1;
	}
	puts("Data Send\n");
	//Terima reply
	if( recv(socket_desc, server_reply , 2000 , 0) < 0)
	{
		puts("recv failed");
	}
	puts("Reply received\n");
	//Tulis reply
	puts(server_reply);
	close(socket_desc);
	return 0;
}


