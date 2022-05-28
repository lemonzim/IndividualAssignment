#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<time.h>//to use time()
#include<stdint.h>//to use intmax_t
#include<stdlib.h>//to use free()
//#include<limits.h>
int main(int argc , char *argv[])
{
	int socket_desc , new_socket , c;
	struct sockaddr_in server , client;
	char client_reply[2000];
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);//Use tcp
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(37);//port37
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed again");
		return 1;
	}
	puts("bind done\n");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("Connection accepted");
		
		//Reply to the client
		time_t result = time(NULL);
		char *mes1="Seconds from Epoch in Binary before flipped: ";
		char mes2[100];
		char *mes3="\nSeconds from Epoch in Binary: ";
		char mes4[100];
		char *mes5="\nActual seconds from Epoch: ";
		char mes6[50];
		int a[100];
		int buf_result=result;
		for(int i=0;buf_result>0;i++)    
			{    
			a[i]=buf_result%2;
			buf_result=buf_result/2;
			sprintf(&mes2[i], "%d", a[i]);
			} 
		//send mes 1,mes 2
		write(new_socket ,mes1 , strlen(mes1));
		write(new_socket ,mes2 , strlen(mes2));
		//for loop to reverse mes2 string which is the binary
		for(int i=0;i<=strlen(mes2)-1;i++)
		{
			//put the first value of mes 4 with the last value of mes2, 2nd one with the last 2nd,and so on....
			mes4[i]=mes2[strlen(mes2)-1-i];
		}
		//send mes 3-6
		write(new_socket ,mes3 , strlen(mes3));
		write(new_socket ,mes4 , strlen(mes4));
		write(new_socket ,mes5 ,strlen(mes5) );
		sprintf(mes6, "%ld", (intmax_t) result);//change int to string
		write(new_socket ,mes6 ,strlen(mes6) );
	}
		if( recv(socket_desc, client_reply , 2000 , 0) < 0)
	{
		puts("recv failed");
	}
	puts("Reply received\n");
	
	if (new_socket<0)
	{
		perror("accept failed");
		return 1;
	}
	return 0;
}
