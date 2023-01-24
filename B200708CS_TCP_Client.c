#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

int main()
{

   /*struct sockaddr_in serv_addr;
  struct hostent *server;
  int sockfd,newsockfd,portno,n;
  char buffer[255];
 // portno=atoi(argv[2]);
 portno=9898;
  
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  
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
    
    bcopy((char *) server->h_addr,(char *) &serv_addr.sin_addr.s_addr,server->h_length);*/
   struct sockaddr_in client;
   
   int sock=socket(AF_INET,SOCK_STREAM,0);
   if(sock<0)
   {
     printf("error in socket creation");
     exit(1);
   }
   
   int portno=8888;
   client.sin_family=AF_INET;
   client.sin_port=htons(portno);
   //client.sin_addr.s_addr=INADDR_ANY;
   int t2=inet_pton(AF_INET,"127.0.0.1",&(client.sin_addr));
  // memset(&(client.sin_zero),'\0',8*sizeof(char));
   
   int t=connect(sock,(struct sockaddr *)&client,sizeof(client));
   if(t<0)
   {
     printf("error in connecting");
     exit(1);
   }
   
   char buffer[255];
   memset(buffer,0,sizeof(buffer));
   printf("enter string as a input:");
   fgets(buffer,255,stdin);
   printf("client:%s",buffer);
   int snd=send(sock,buffer,strlen(buffer),0);
   if(snd<0)
   {
     printf("error in sending");
     exit(1);
   }
   
   memset(buffer,0,sizeof(buffer));
   int rcv=recv(sock,buffer,255,0);
   if(rcv<0)
   {
     printf("error in recieving");
     exit(1);
   }
   printf("server:%s",buffer);
   return 0;
   close(sock);
}
