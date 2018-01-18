#ifndef _LINK
#define _LINK
typedef struct linklist
{
	char name[10];
	char passwd[10];
	struct linklist * next;
}LINKLIST;



LINKLIST * create_Linklist();
int add_Linklist(LINKLIST * head,char *user,char * pwd);
int delete_Linklist(LINKLIST * head,char * user,char * pwd);
int update_Linklist(LINKLIST * head,char * user,char * pwd,char * newpwd);
int search_Linklist(LINKLIST* head,char * user,char * pwd);
int show_Linklist(LINKLIST * head);
int save_Linklist(LINKLIST * head);
int load_Linklist(LINKLIST * head);
int submit_file(LINKLIST * head,char * filename);
int download_file(LINKLIST * head,char * filename);
//int tail_Linklist(LINKLIST* head,SD_MSG * msf);
//int invert_Linklist(LINKLIST * head);
/*int is_circle_Linklist(LINKLIST * head);*/
#endif

