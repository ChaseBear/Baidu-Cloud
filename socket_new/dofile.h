#ifndef __DOFILE__
#define __DOFILE__
int unload(int sockfd,char * buf);
int download(int sockfd,char * buf);
int submit_file_server(int sockfd,char * buf);
int download_file_server(int sockfd,char * buf);

#endif
