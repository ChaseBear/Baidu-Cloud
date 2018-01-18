#include "linklist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<strings.h>
LINKLIST * create_Linklist()
{
  LINKLIST *point =(LINKLIST *)malloc(sizeof(LINKLIST));
  if(point==NULL)
  {
     printf("apply fail\n");
	 return NULL;

  }
  point->next=NULL;
   return point;
}
/*
int tail_Linklist(LINKLIST * head,SD_MSG * msg)
{

    LINKLIST * p =head;
    while(p->next!=NULL)
	{
      p=p->next;
	}
    LINKLIST * point =(LINKLIST *)malloc(sizeof(LINKLIST));
	if(point==NULL)
	{   
		perror("fail");
         return -1;
	}
    p->next=point;
	strcpy(point->name,msg->name);
	point->passwd=(msg->passwd);
	printf("add success!\n");
	p=p->next;
	p->next=NULL;
	return 0;
}
*/


int delete_Linklist(LINKLIST * head,char * user,char * pwd)
{
	LINKLIST * temp=NULL;
	LINKLIST * p=head;
	while(p->next!=NULL)
	{
      if(p->next==NULL)
	  {
			 return -1;
	  }

	  if(strcmp(p->next->name,user)==0)
	  {
		  if(strcmp(p->next->passwd,pwd)==0)
		  {
              temp=p->next;
		      p->next=temp->next;
		      free(temp);
		      return 0;
	      }

		  else
		  {
             printf("passwd error!\n");
			 return -1;
		  }
	  }
       
	  else
	  {
		  printf("input user error!\n");
		  return -1;
	  }
        
	  p=p->next;
	}
	return -1;
}

int update_Linklist(LINKLIST * head,char* user,char * pwd,char* newpwd)
{
    int i;
	LINKLIST * p=head;
	while(p->next!=NULL)
	{
		p=p->next;
		printf("++++++++\n");
       if(strcmp(p->name,user)==0)
	   {
		   printf("--------\n");
          if(strcmp(p->passwd,pwd)==0)
		  {
			  printf("*********\n");
              strcpy(p->passwd,newpwd);
			  return 0;
		  }     
	    } 

	}

	return -1;

}

int search_Linklist(LINKLIST * head,char * user,char * pwd)
{
   LINKLIST * p=head;
   int i=0;
   while(p->next!=NULL)
   {
       p=p->next;
	   if(strcmp(p->name,user)==0)
	   {
		  if(strcmp(p->passwd,pwd)==0){
            printf("%s %s",user,pwd);
		  return 0;
		  }
	   }

   }
    return -1;
}

int show_Linklist(LINKLIST * head)
{
   LINKLIST * p=head;
   if(p->next==NULL)
   {
      printf("no data!\n");
	  return -1;
   }
   printf("***********************\n");
   printf("***********************\n");
   while(p->next!=NULL)
   {
      p=p->next;
	  printf("current data:%s %s\n",p->name,p->passwd);

   }

    return 0;

}
int add_Linklist(LINKLIST * head,char * user,char * pwd)
{
	LINKLIST * p=head;
    LINKLIST * point =(LINKLIST *)malloc(sizeof(LINKLIST));
    if(point==NULL)
	{
         printf("input error!\n");
		 return -1;
	}
	strcpy(point->name,user);
	strcpy(point->passwd,pwd);
    point->next=p->next;
	p->next=point;
	return 0;

}
/*
int invert_Linklist(LINKLIST * head)
{
	LINKLIST * p=head;
	LINKLIST * temp;
	LINKLIST * old=head->next;
    p->next=NULL;
   while(old!=NULL)
   {
	    temp=old;
		old=old->next;
		temp->next=p->next;
		p->next=temp;
	
   }
       return 0;

}
*/
/**
int is_circle_Linklist(LINKLIST * head)
{
   LINKLIST * p=head;
   LINKLIST * q=head;
   while(q->next->next!=NULL||q->next->next!=head)
   {
      p=p->next;
	  q=q->next->next;
	  if(q==p)
	  {
        return 1;
	  }
   }
   return 0;
}
*/
/*
void load_list(LINKLIST*L)
{

	sqlite3   *db;        
   	if(sqlite3_open("my.db",  &db)  !=  SQLITE_OK)
	{
		printf("error : %s\n", sqlite3_errmsg(db));
		exit(-1);  
   	}
  
	while(1)
	{
		printf("myDBMS> ");fflush(stdout);
		char sqlbuf[100] = {0};
        sprintf(sqlbuf,"insert into <mydb> values(username,passwd)", );
   		sqlite3_exec(db," ",  sqlite3_callback callback, void *,  char **errmsg);
		char *errmsg;
		if  (sqlite3_exec(db, sqlbuf,  myfunc,  NULL, &errmsg) !=  SQLITE_OK)
		{
			printf("error :  %s\n",  errmsg);
			exit(-1);
		}
	}


}
*/

int save_Linklist(LINKLIST * head)
{
	LINKLIST * p=head;
    int ret;
    ret=open("./base.db",O_WRONLY|O_CREAT|O_TRUNC,0664);
	if(ret<0)
	{
        perror("open fail!");
		return -1;
    }

    while(p->next!=NULL)
	{
	   p=p->next;
       write(ret,p->name,10);
	   write(ret,p->passwd,10);
	}
	close(ret);
}


int load_Linklist(LINKLIST * head)
{
	LINKLIST * p=head;
    int ret,n;
	char userarr[11]={'\0'};
	char passarr[11]={'\0'};
	ret=open("base.db",O_RDONLY);
	if(ret<0)
	{
	   perror("no data\n");
	   return -1;
	}
	while(n!=0)
   {
	  n =read(ret,userarr,10);
      read(ret,passarr,10);
      add_Linklist(p,userarr,passarr);
	  bzero(userarr,sizeof(userarr));
	  bzero(passarr,sizeof(passarr));
   }
	close(ret);
   if(n==0)
   return 0;
   else
   {
      printf("read fail!\n");
      return -1;
   }
}


