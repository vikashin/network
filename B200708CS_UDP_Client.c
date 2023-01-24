#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

int main()
{
 
  /*if(argc < 3)
  {
     printf("port No not provided. Program terminated\n");
     exit(1);
  }*/
  
  struct sockaddr_in serv_addr;
  struct hostent *server;
  int sockfd,newsockfd,portno,n,clilen;
  char buffer[255];
  portno=9898;
  
  sockfd=socket(AF_INET,SOCK_DGRAM,0);
  
  if(sockfd<0)
  {
    printf("error opening socker\n");
    exit(1);
  }
  
  server=gethostbyname("127.0.0.1");
  if(server==NULL)
  {
    printf("error, no such host\n");
  } 
    bzero((char *) &serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    
    bcopy((char *) server->h_addr,(char *) &serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port=htons(portno);
  /*if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
        {
           printf("Bnding Failed\n");
           exit(1);
        }*/
 clilen=sizeof(serv_addr);
 bzero(buffer,255);
 
 printf("enter a string as input:");
 fgets(buffer,255,stdin);
 
 n=sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *) &serv_addr,clilen);
 if(n<0)
 {
   printf("error in sending\n");
   exit(1);
 
 }
 
 bzero(buffer,255);
 n=recvfrom(sockfd,buffer,255,0,(struct sockaddr *) &serv_addr,&clilen);
 if(n<0)
 {
   printf("error from recieving\n");
  
  exit(1);
 }
 printf("server response is:%s\n",buffer);
 return 0;       
}
