#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
 #include <sys/stat.h>
 #include <fcntl.h>
#include<stdlib.h>
#define N 30
#define M 10
#define NAME 10


int unload(int sockfd,char * filename );//client
int download(int sockfd,char * filename);//client
int create_socket();

int fw;
int main(int argc, char *argv[])
{
	char buf[N];
	if(3 != argc)
	{
		printf("Usage: %s <IP> <PORT>\n", argv[0]);
		return -1;
	}
    
	//需要网络通信就要调用socket()创建套接字
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	//Tcp主动端需要调用connect()检测通路
	struct sockaddr_in serveraddr = {0};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));	
	int len = sizeof(serveraddr);

	if(-1 == connect(fd, (struct sockaddr *)&serveraddr, len) )
	{
		perror("connect ");
		return -1;
	} 

		//发送数据
			printf("/******************************************/\n");
			printf("/*  help                                  */\n");
			printf("/*  1.注册用户 insert <name>  <passwd>    */\n");
			printf("/*  2.删除用户delete <name>  <passwd>     */\n");
			printf("/*  3.更新用户update <name>  <passwdo> <passwdn>*/\n");
			printf("/*  3.查找用户search <name>  <passwd>     */\n");
			printf("/*  4.退出 quit                           */\n");
            printf("/*  5.上传文件 put <filename>             */\n");
		    printf("/*  6.下载文件 get <filename>             */\n");	
			printf("/******************************************/\n");
	 
	while(1)
	{
		printf("database> ");fflush(stdout);
/*********send msg**************/
		printf("please input cmd!\n");
		fgets(buf,N,stdin);
        buf[strlen(buf)-1]='\0';
		write(fd, buf,strlen(buf));
/*******send filename********/
        if(strncmp(buf,"put",3)==0)
		{
           unload(fd,buf);
		}

		else if(strncmp(buf,"get",3)==0)
		{
          download(fd,buf);
		}
         
		else if(strncmp(buf,"ls",2)==0)
		{
          
           search_dir(buf);
		}
		else
		{
			if(strncmp(buf,"quit",4)==0)
			{
             break;
			}
		}
        /*******recive msg*************/
		read(fd, buf, N);
		if(strncmp(buf,"login success",13)==0)
		{
		  pid_t pid;
		  pid=fork();
		  if(pid<0)
		  {
            perror("fork fial!");
			return -1;
		  }

		  else if(pid==0)
		  {
             create_socket();
		  }

		  else
		  {
            exit(0);
		  }

		}
		printf("recv : %s\n", buf);
	}
	close(fd);

    return 0;
}


int unload(int sockfd,char * filename )//client
{
   int ret,n=1;
   char buf[100]={0};
   struct stat st;
   printf("11111111111111111\n");
   stat(filename+4,&st);
   sprintf(buf,"%ld",st.st_size);
   write(sockfd,buf,100);//文件大小
   int size=atoi(buf);
   printf("%d\n",size);
   printf("222222222222222222\n");

   ret=open(filename+4,O_RDONLY);
   printf("%s\n",filename+4);
   
   printf("打开成功\n");
   if(ret<0)
   { 
     perror("open fail!");
   }

   bzero(buf,strlen(buf));
   while(size)
   {
      n=read(ret,buf,100);
      printf("size is:%d\n",n);
	  write(sockfd,buf,n);
	  size-=n;
   }

   if(size==0)
   {
      printf("submit success!\n");
   }

   close(ret);
   return 0;
}


int download(int sockfd,char * filename)//client
{
   char buf[100]={0};
   char real_buf[20]={0};
   strcpy(real_buf,filename+4);
   printf("filename %s\n",real_buf);

   read(sockfd,buf,100);//文件大小
   int size=atoi(buf);
   printf("size:%d\n",size);//文件大小

   int ret,i=0;
   ret=open(real_buf,O_WRONLY|O_CREAT|O_TRUNC,0664);
   if(ret<0)
   {
      perror("open fail!");
	  return -1;
   }
   memset(buf,0,100);
   int n=1;
   char msf[100]={0};
   while(n!=0)
   {
      n=read(sockfd,msf,100);
	  printf("read count:%d\n",n);
      write(ret,msf,n);
   }
   close(ret);
   
   if(size==0)
   {
	   char str[20]={0};
	   read(sockfd,str,20);
	   printf("%s\n",str);

   }
   
   return 0;
}

int search_dir(char * buf)
{
  system(buf);
  return 0;
}


int create_socket()
{
  //  while(1 )
 // {
	//需要网络通信就要调用socket()创建套接字
	fw = socket(AF_INET, SOCK_STREAM, 0);

	//Tcp主动端需要调用connect()检测通路
	struct sockaddr_in serveraddr = {0};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(atoi("9999"));	
	int len = sizeof(serveraddr);

	if(-1 == connect(fw, (struct sockaddr *)&serveraddr, len) )
	{
		perror("connect ");
		return -1;
	} 
    
	while(1); 
		//发送数据
			printf("/******************************************/\n");
			printf("/*  help                                  */\n");
			printf("/*  1.注册用户 insert <name>  <passwd>    */\n");
			printf("/*  2.删除用户delete <name>  <passwd>     */\n");
			printf("/*  3.更新用户update <name>  <passwdo> <passwdn>*/\n");
			printf("/*  3.查找用户search <name>  <passwd>     */\n");
			printf("/*  4.退出 quit                           */\n");
            printf("/*  5.上传文件 put <filename>             */\n");
		    printf("/*  6.下载文件 get <filename>             */\n");	
			printf("/******************************************/\n");
	printf("database> ");fflush(stdout);
/*********send msg**************/
		printf("please input cmd!\n");
		fgets(buf,N,stdin);
        buf[strlen(buf)-1]='\0';
		write(fd, buf,strlen(buf));
/*******send filename********/
        if(strncmp(buf,"put",3)==0)
		{
           unload(fd,buf);
		}

		else if(strncmp(buf,"get",3)==0)
		{
          download(fd,buf);
		}
         
		else if(strncmp(buf,"ls",2)==0)
		{
          
           search_dir(buf);
		}
		else
		{
			if(strncmp(buf,"quit",4)==0)
			{
             break;
			}
		}
        /*******recive msg*************/
		read(fd, buf, N);
		printf("buf=%s \n",buf);
			return 0;
//	}

}
