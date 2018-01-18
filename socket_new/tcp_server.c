#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "linklist.h"
#include <stdlib.h>
//#include <sqlite3.h>


#define  N  sizeof(struct send_msg)
void adduser(LINKLIST * head,char * username,char * passwd,char * buf);
void deleteuser(LINKLIST * head,char * username,char * passwd,char * buf);
void update(LINKLIST * head,char * username,char * passwd,char * newpasswd,char * buf);
void login(LINKLIST * head,char * username,char * passwd,char * buf);



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
     
    int on=1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(int));
	
	struct sockaddr_in serveraddr = {0};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");//代表自己电脑的所有ip
	serveraddr.sin_port = htons(8888);	//绑定确定端口，以便于客户端连接定位
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
		   perror("create fork fail!\n");
		    return 0;
	    }

	     else if(pid==0)
        {    
		 // close(fd);
		  LINKLIST * head;
		  head=create_Linklist();
	       char buf[30]={'\0'};
		   char username[10]={'\0'};
		   char passwd[10]={'\0'};
		    char newpasswd[20]={'\0'};
           int state=2;
		 load_Linklist(head);
		 show_Linklist(head);

	     while(1)
	   {

		read(clientfd,buf,sizeof(buf));
		if(strncmp(buf,"save",4)==0){
			printf("begin keep linklist!\n");
           save_Linklist(head);
		}
            
       else
       {
		   if(strncmp(buf,"insert",6)==0)
           adduser(head,username,passwd,buf);


		   else
		   {
             if(strncmp(buf,"delete",6)==0)
             deleteuser(head,username,passwd,buf);

				 else
				  {
                       if(strncmp(buf,"update",6)==0)
                        update( head,username, passwd,newpasswd, buf);

                       else if(strncmp(buf,"login",5)==0)
                         login(head,username,passwd,buf);

					   else
					   {
						   if(strncmp(buf,"quit",4)==0)
						   {
						       printf("%s\n",buf);
						   }

						   else
							{
						       strcpy(buf,"input error!\n");
						        break;
							}
					   }
				  }
			   }
		   }
             sleep(1);
		     write(clientfd,buf,strlen(buf));
			 memset(buf,0,30);
			 printf("recv:%s",buf);
	  }
	   
		//printf("%s %s %ld\n",rec_buf.cmd,rec_buf.name,rec_buf.passwd);

    }

	   close(clientfd);
  }
	return 0;
}

void adduser(LINKLIST * head,char * username,char * passwd,char * buf)
{
	          int state=0;
  
             mycopy(passwd,mycopy(username,buf+7));
			// username[strlen(username)]='\0';
			// passwd[strlen(passwd)]='\0';
			// printf("%s %s\n",username,passwd);

				printf("****************\n");
			    state=add_Linklist(head,username,passwd);
				printf("****************\n");
				if(state==0)
				{
				    show_Linklist(head);
				}
				else
				{
				   printf("input error!\n");
				}
}


void deleteuser(LINKLIST * head,char * username,char * passwd,char * buf)
{
                    int state; 
                    mycopy(passwd,mycopy(username,buf+7));
				    printf("****************\n");
					state=delete_Linklist(head,username,passwd);
					if(state==0)
					{
                         printf("delete success\n");
					}
				    printf("****************\n");
					memset(buf,0,30);
				    strcpy(buf,"delete OK");		
				    show_Linklist(head);

}
void update(LINKLIST * head,char * username,char * passwd,char * newpasswd,char * buf)
{                    
                         int state;
                        mycopy(newpasswd, mycopy(passwd,mycopy(username,buf+7)));
						state=update_Linklist(head,username,passwd,newpasswd);
                          
				          printf("****************\n");
						  if(state==0)
					    {		  
						  printf("update success!\n");
					    }
				          printf("****************\n");
				          show_Linklist(head);
					   

}
void login(LINKLIST * head,char * username,char * passwd,char * buf)
{
                          int state;
                          mycopy(passwd,mycopy(username,buf+7));
						  state=search_Linklist(head,username,passwd);

				          printf("****************\n");
						  if(state==0)
						  {
                             printf("login success!\n"); 
						  }

				          printf("****************\n");
						  strcpy(buf,"login success");

}
