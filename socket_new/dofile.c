 #include<stdio.h>
 #include<string.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
#include<stdlib.h>
 #include "dofile.h"



int submit_file_server(int sockfd,char * filename)//server
{
   char rel_name[20]={0};
   strcpy(rel_name,filename+4);
   printf("filename :%s\n******",rel_name);//文件名
   char buf[100]={0};
   if(strncmp(rel_name,"put",3)!=0)
   printf("文件接收到\n");
   
   read(sockfd,buf,100);//读文件大小
   int size=atoi(buf);
   printf("size is:%d\n",size);
   

   int ret;
   ret=open(rel_name,O_WRONLY|O_CREAT|O_TRUNC,0664);
   if(ret<0)
   { 
     perror("open fail!");
	 return -1;
   }
    printf("文件打开成功\n");
   int n=1;

    printf("开始传输\n");
	bzero(buf,strlen(buf));
   while(size)
   {
      n=read(sockfd,buf,100);
	  printf("size:%d\n",n);
	  write(ret,buf,n);
	  size-=n;
   }
   if(size==0)
   {
      printf("submit success!\n");
	  char str[20]="submit success!";
	  write(sockfd,str,20);
   }
   close(ret);
   return 0;
}


int  download_file_server(int sockfd,char * filename)//server
{
   printf("filename:%s\n",filename+4); 
   int ret;
   char buf[100]={0};
   char real_name[20];
   strcpy(real_name,filename+4);
   struct stat s;
   printf("获取文件状态\n！");
   stat(real_name,&s);
   sprintf(buf,"%ld",s.st_size);
   int size=atoi(buf);
   printf("file size:%d\n",size);
   write(sockfd,buf,size);//文件大小
   printf("%s\n",buf);
   ret=open(real_name,O_RDONLY,0664);

   printf("file size:%d\n",size);
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
      n=read(ret,msf,100);
	  printf("read count:%d",n);
	  printf("msf=%s\n",msf);
      write(sockfd,msf,n);
	  size-=n;
   }
   
   printf("%d\n",size);
   close(ret);
   memset(msf,0,100);
   sleep(1);
   if(size==0)
   { 
	   printf("download success!\n");
	   char str[20]="####ok*";
	   write(sockfd,str,100);
   }
   
   return 0;
 }

int client_file_server(int sockfd,char * buf)//server
{

    system(buf);
	return 0;

}

