 #include<stdio.h>
 #include<string.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include "dofile.h"

int unload(int sockfd,char * filename )//client
{
   int ret,n;
   int size;
   write(sockfd,filename,100);
   char buf[100]={0};
   struct stat st;
   printf("11111111111111111\n");
   stat(filename+4,&st);
   printf("%s\n",filename+4);
   printf("size is:%d",atoi(filename));
   
   printf("222222222222222222\n");
   ret=open(filename+4,O_RDONLY);
   printf("%s\n",filename+4);
   
   printf("3333333333333333\n");
   if(ret<0)
   { 
     perror("open fail!");
   }

   bzero(buf,strlen(buf));
   while(n!=0)
   {
      n=read(ret,buf,100);
	  printf("%d\n",n);
	  write(sockfd,buf,n);
   }

   if(n==0)
   {
      printf("submit success!\n");
   }

   close(ret);
}

int download(int sockfd,char * filename)//client
{
   char buf[100]={0};
   write(sockfd,filename,100);
   int ret;

   ret=open(filename+4,O_RDONLY|O_CREAT|O_TRUNC,0664);
   if(ret<0)
   {
      perror("open fail!");
	  return -1;
   }
   int n=1;
   while(n!=0)
   {

      n=read(sockfd,buf,100);
      write(ret,buf,n);
   }
   close(ret);
}

int submit_file_server(int sockfd,char * filename)//server
{
   
   int ret;
   char buf[100]={0};
   read(sockfd,buf,100);
   printf("%s\n",filename+4);
   printf("11111111111111111\n");
   ret=open(filename+4,O_WRONLY|O_CREAT|O_TRUNC,0664);
   if(ret<0)
   { 
     perror("open fail!");
	 return -1;
   }
    printf("2222222222222\n");
   int n=1;
   while(n!=0)
   {
      printf("333333333\n");
      n=read(sockfd,buf,1000);
	  printf("%d \n",n);
	  write(ret,buf,n );
   }
   if(n==0)
   {
      printf("submit success!\n");
	  char str[20]="submit success!";
	  write(sockfd,str,20);
   }
   close(ret);
}


int  download_file_server(int sockfd,char * filename)//server
{
   
   char buf[20]={0};
   read(sockfd,buf,100);
   int ret;
   ret=open(filename+4,O_RDONLY|O_CREAT|O_TRUNC,0664);
   if(ret<0)
   {
      perror("open fail!");
	  return -1;
   }
   int n=1;
   while(n!=0)
   {
      n=read(ret,buf,100);
      write(sockfd,buf,n);
   }
   if(n==0)
   { 
	   printf("download success!\n");
	   char str[20]="download success";
	   write(sockfd,str,20);
   }
   close(ret);
 }



