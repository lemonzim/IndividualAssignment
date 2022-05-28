#include <stdio.h>
#include <sys/socket.h>
#include <string.h> // to use strlen
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write
#include <stdlib.h>
#include <sys/socket.h>
int main(int argc , char *argv[])
{
	int socket_desc,c;
	struct sockaddr_in server; 
	char *message, server_reply[2000];
	//Create socket
	socket_desc = socket(AF_INET , SOCK_DGRAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
		
	server.sin_addr.s_addr = inet_addr("192.168.56.105");
	server.sin_family = AF_INET;
	server.sin_port = htons(37);
	
	puts("Client wants total seconds from Epoch\n");

	//Send some data
	message ="Date";
	if(sendto(socket_desc, message, strlen(message)+1, 0, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		puts("Send failed");//output if error
		return 1;
	}
	puts("Data Send\n");
	//Receive a reply from the server
	c = sizeof(server);
	if(recvfrom(socket_desc, server_reply, sizeof(server_reply), 0, (struct sockaddr*)&server, &c) < 0)
	{
		puts("recv failed");
	}
	puts("The number of seconds since Epoch time (00:00 (midnight) 1 January, 1900 GMT) in Binary");
	puts(server_reply);
close(socket_desc);
	return 0;
}


