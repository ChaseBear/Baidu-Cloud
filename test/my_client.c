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
#define N 100
#define M 10
#define NAME 10
int unload(int sockfd,char * filename );//client
int download(int sockfd,char * filename);//client
int create_socket();
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
			printf("/*  2.登录用户 login <name>  <passwd>     */\n");
			printf("/*  3.更新用户update <name>  <passwdo> <passwdn>*/\n");
			printf("/*  4.删除用户 delete <name>  <passwd>     */\n");
			printf("/*  5.保存用户 save(保存用户必须先输入exit退出文件服务器)*/\n");
			printf("/*  6.退出文件服务 exit                   */\n");
			printf("/*  7.退出数据服务 quit                   */\n");
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
			/*
		    pid_t pid;
			if(pid==-1)
			{
               perror("create fail!\n");
			   return -1;
			}

			else if(pid==0)
			{*/
              create_socket();

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
   sleep(1);
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
   while(size)
   {
      n=read(sockfd,msf,100);
	  printf("read count:%d\n",n);
	  if(strncmp(msf,"####ok*",7)==0)
	  {
	  break;
	  }
      write(ret,msf,n);
	  size-=n;
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
  //printf("ls ok \n");
  return 0;
}


int create_socket()
{
	int fd;
	//需要网络通信就要调用socket()创建套接字
	fd = socket(AF_INET, SOCK_STREAM, 0);
	char buf[100]={0};
	//Tcp主动端需要调用connect()检测通路
	struct sockaddr_in serveraddr = {0};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(atoi("9999"));	
	int len = sizeof(serveraddr);

	if(-1 == connect(fd, (struct sockaddr *)&serveraddr, len) )
	{
		perror("connect ");
		return -1;
	}

    	printf("/******************************************/\n");
		printf("/*  help                                  */\n");
		printf("/*  1.上传文件 put <filename>             */\n");
		printf("/*  2.下载文件 get <filename>             */\n");	
		printf("/*  3.查看本地文件 ls                     */\n");
		printf("/*  4.退出         exit                   */\n");	
		printf("/******************************************/\n");

	while(1){ 
		//发送数据
		printf("database> ");fflush(stdout);
		/*********send msg**************/
		printf("please input cmd!\n");
		fgets(buf,100,stdin);

		buf[strlen(buf)-1]='\0';
		printf("%d \n",__LINE__);
		write(fd, buf,100);
		printf("%d \n",__LINE__);
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

		printf("%d \n",__LINE__);
			search_dir(buf);
		}
		else
		{
			if(strncmp(buf,"exit",4)==0)
			{
				break;
			}
		}
		/*******recive msg*************/
		read(fd, buf, 100);
		printf("buf=%s \n",buf);
	}
return 0;

}
