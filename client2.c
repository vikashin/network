#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include<fcntl.h>

#define PORT 8888
#define MAX_NAME_SZE 10
#define size 1024
int main()
{
  struct sockaddr_in client;
  int sock;
  sock=socket(AF_INET,SOCK_STREAM,0);
  if(sock<0)
   {
     printf("error in socket creation");
     exit(1);
   }
   
   
   client.sin_family = AF_INET;
   client.sin_port = htons(PORT); 
   client.sin_addr.s_addr = INADDR_ANY;
   
  fd_set readfd;
 
  
  int max_fd;
  max_fd=sock;
  
  
  
  
  int tmp=connect(sock,(struct sockaddr *)&client,sizeof(client));
  if(tmp<0)
  {
    printf("error in connecting");
    exit(1);
  }
  
  char buffer[255];
  memset(buffer,0,255);
  while(1)
  {
      FD_ZERO(&readfd);  
  FD_SET(sock,&readfd);
  FD_SET(STDIN_FILENO,&readfd);
  fcntl(STDIN_FILENO,F_SETFL,O_NONBLOCK);
  max_fd=sock;
      int activity=select(max_fd+1,&readfd,NULL,NULL,NULL);
      
       if(activity<=0) {
        exit(1);
      }

     if(FD_ISSET(sock,&readfd)) {
       
        memset(buffer,0,255);
        int nbytes=recv(sock,buffer,255,0);
        if(nbytes<=0)
        {
          printf("client disconected\n");
          close(sock);
          exit(1);
        }
        else
        printf("%s\n",buffer);                
     }

     if(FD_ISSET(STDIN_FILENO,&readfd)) {
         memset(buffer,0,255);
         if(read(0,buffer,255)>0) {
                int nbyte_send=send(sock,buffer,255,0);
                if(nbyte_send<0)
                {
                  printf("error in sending");
                  exit(1);
                }                
        }
                   
     }
 }

return 0;
}

