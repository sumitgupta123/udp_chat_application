#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>

int main()
{
	struct sockaddr_in ser;

	memset(&ser,0,sizeof(ser));

	ser.sin_family=AF_INET;
	ser.sin_port=htons(10000);
	ser.sin_addr.s_addr=INADDR_ANY;

	int sock_id;
	if((sock_id=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("socket:");
		return 0;
	}

	char a[100];
	char b[100];
//	int len;
	while(1)
	{	memset(a,0,100);
		memset(b,0,100);
		printf("client:");
		fgets(a,100,stdin);
		sendto(sock_id,a,strlen(a),0,(struct sockaddr*)&ser,sizeof(ser));
		int len=sizeof(ser);
		recvfrom(sock_id,b,100,0,(struct sockaddr*)&ser,&len);
		printf("server:%s",b);
		if(strcmp(a,"bye\n")==0)
			return 0;
	}
	close(sock_id);
	return 0;
}

