#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <stdlib.h>
#include "dofile.h"
#include<unistd.h>
//#include <sqlite3.h>



/*
void changeC(char *buf)
{
	while(*buf)
	{
		if(*buf>='a' && *buf<='z')
		{
			*buf -= ' ';
		}
		else
		if(*buf>='A' && *buf<='Z')
		{
			*buf += ' ';
		}
		buf++;
	}
}
*/

static char * mycopy(char * dest, char * sor)
{
   while(*sor&&' '!=*sor)
   {
     *dest++ = *sor++;   
   }
   return sor+1;
}



int main(int argc, char *argv[])
{
	//需要网络通信就要调用socket()创建套接字
	int fd = socket(AF_INET, SOCK_STREAM, 0);
     
    int z=1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&z,sizeof(int));
	
	struct sockaddr_in serveraddr = {0};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");//代表自己电脑的所有ip
	serveraddr.sin_port = htons(9999);	//绑定确定端口，以便于客户端连接定位
	int len = sizeof(serveraddr);
	//Tcp server被动端需要调用bind()绑定ip和端口
	
	if(-1 == bind(fd, (struct sockaddr *)&serveraddr, len) )
	{
		perror("connect ");
		return -1;
	}


	listen(fd, 10);//开机等响铃
	printf("listening.........\n");
	
    while(1)
  {
	int clientfd = accept(fd, NULL, NULL);//接电话
	printf("client connected !\n");

	pid_t pid;
	pid=fork();
	if(pid<0)
	{
       perror("open fail!\n");
	   return -1;
	}

	else  if(pid==0)
	{
	   while(1)
	   {
		   char buf[100]={'\0'};

		   read(clientfd,buf,100);
		   printf("buf=%s\n",buf);
		   if(strncmp(buf,"put",3)==0){
			   submit_file_server(clientfd,buf);

		   }
		   else if(strncmp(buf,"get",3)==0)
		   {
			   download_file_server(clientfd,buf);
		   }

		   else  if(strncmp(buf,"quit",4)==0)
		   {
			   break;
		   }
		   printf("Ok 88888888888\n");
		   write(clientfd,buf,100);
	   }
	}
    close(clientfd);
  }
	return 0;
}
