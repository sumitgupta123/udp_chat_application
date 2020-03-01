#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>

int main()
{
	struct sockaddr_in ser,cli;
	memset(&ser,0,sizeof(ser));
	memset(&cli,0,sizeof(cli));

	ser.sin_port=htons(10000);
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=INADDR_ANY;

	int sock_id;

	if((sock_id=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("socket:");
		return 0;
	}

	bind(sock_id,(struct sockaddr*)&ser,sizeof(ser));

	char a[100];
	char b[100];

	while(1)
	{
		memset(a,0,100);
		memset(b,0,100);
		int len=sizeof(cli);
		recvfrom(sock_id,a,100,0,(struct sockaddr*)&cli,&len);
		printf("client:%s",a);
		printf("server:");
		fgets(b,100,stdin);
		sendto(sock_id,b,strlen(b),0,(struct sockaddr*)&cli,len);
	}
	close(sock_id);
	return 0;
}
