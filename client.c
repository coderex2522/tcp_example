#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in server_addr;
	int client_sockfd, err, cnt=0;
	char send_buff[BUFSIZ], recv_buff[BUFSIZ];

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("192.168.206.129");
	server_addr.sin_port=htons(39400);

	client_sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(client_sockfd<0)
	{
		perror("socket call error.");
		return -1;
	}

	err=connect(client_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(err)
	{
		perror("connect call error.");
		return -1;
	}
	
	while(1)
	{
		snprintf(send_buff, BUFSIZ, "client current cnt is %d",cnt);
		cnt+=2;

		err=write(client_sockfd, send_buff, strlen(send_buff)+2);
		if(err<=0)
		{
			printf("connection close or exist error.\n");
			break;
		}
		
		read(client_sockfd, recv_buff, BUFSIZ-1);
		if(err<=0)
		{
			printf("connection close or exist error.\n");
			break;
		}
		
		printf("%s\n",recv_buff);
		
		sleep(2);
	}

	close(client_sockfd);
	return 0;
}