#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<time.h>//to use time()
#include<stdint.h>//to use intmax_t
#include<stdlib.h>//to use free()
#include<limits.h>
int main(int argc , char *argv[])
{
	int socket_desc, c;
	struct sockaddr_in server, client;
	char client_reply[2000];
	
	//Create socket
	socket_desc = socket(AF_INET ,SOCK_DGRAM , 0);//Use tcp
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(37);
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed again");
		return 1;
	}
	puts("bind done\n");
	
	//Accept and incoming connection
	c = sizeof(struct sockaddr_in);
	while(recvfrom(socket_desc,client_reply, sizeof(client_reply), 0, ( struct sockaddr *)&client, &c))
	{
		puts("Reply received\n");
		//Reply to the client
		time_t result = time(NULL);
		char mes1[100];
		char mes2[100];
		int a[100];
		int buf_result=result;
		for(int i=0;buf_result>0;i++)    
			{    
			a[i]=buf_result%2;
			buf_result=buf_result/2;
			//change the int to string
			sprintf(&mes1[i], "%d", a[i]);
			}
		for(int i=0;i<=strlen(mes1)-1;i++)
		{
			//replace first value of mes 2 with the last value of mes1, 2nd one with the last 2nd,and on....
			mes2[i]=mes1[strlen(mes1)-1-i];
		}
		sendto(socket_desc, mes4, strlen(mes1)+1, MSG_CONFIRM, (struct sockaddr*)&client, sizeof(client)); 
	}
	
	if (socket_desc<0)
	{
		perror("accept failed");
		return 1;
	}
	return 0;
}
