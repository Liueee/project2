#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
 

int main(int argc, char *argv[])
{ 
 int sockfd,new_fd; 
 struct sockaddr_in server_addr; 
 struct sockaddr_in client_addr; 
 int sin_size,portnumber; 

 char name[]="学号202234266005 姓名刘采玟"; 
 /*
char len[30] = {0};
time_t lt;
lt =time(NULL);
snprintf(len,30,ctime);
//printf(ctime(&lt));
*/
  char len[30] = {0};

    time_t timestamp;
    time(&timestamp);

    struct tm *p;
    struct tm *local;

    p = gmtime(&timestamp);
    local=localtime(&timestamp);

    char *wday[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
    char *mon[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec"};
    snprintf(len, 30, "%s %s %d %d:%d:%d %d",wday[p->tm_wday], mon[p->tm_mon], p->tm_mday , local->tm_hour, p->tm_min, p->tm_sec,1900+p->tm_year);
  //  printf("\n%s\n", len);


 if((portnumber=atoi(argv[1]))<0) 
 { 
  fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]); 
  exit(1); 
 } 

/* ?????��?��??�?��???建�??socket???述�??1?7? */ 
 if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)   
 { 
        fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
        exit(1); 
 } 

/* ?????��?��??�?�??? sockaddr�?????  */  
 bzero(&server_addr,sizeof(struct sockaddr_in)); 
 server_addr.sin_family=AF_INET; 
 server_addr.sin_addr.s_addr=htonl(INADDR_ANY); 
 server_addr.sin_port=htons(portnumber); 
  
/* ???�??sockfd???述�??1?7?  */  
 if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
 { 
        fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
        exit(1); 
 } 
  
/* ?????�sockfd???述�??1?7?  */ 
 if(listen(sockfd,5)==-1) 
 { 
        fprintf(stderr,"Listen error:%s\n\a",strerror(errno)); 
        exit(1); 
 } 

 while(1) 
 { 
        /* ?????��?��?��??1?7?,??��?��????��??�??建�??�?????  */ 
        sin_size=sizeof(struct sockaddr_in); 
        if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1) 
        { 
                fprintf(stderr,"Accept error:%s\n\a",strerror(errno)); 
                exit(1); 
    } 

        fprintf(stderr,"Server get connection from %s\n", 
                                        inet_ntoa(client_addr.sin_addr)); 
        if(write(new_fd,name,strlen(name))==-1) 
        { 
         fprintf(stderr,"Write Error:%s\n",strerror(errno)); 
         exit(1); 
        } 
        if(write(new_fd,len,strlen(len))==-1) 
        { 
         fprintf(stderr,"Write Error:%s\n",strerror(errno)); 
         exit(1); 
        }
/* �??�?�???�?已�???�?????     */ 
        close(new_fd); 
/* �?�??��??�??�??1?7?     */   
} 
 close(sockfd); 
 exit(0); 
} 