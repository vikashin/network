#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void reverse(char *str)
{
  int len=strlen(str);
   char str1[len-1];
   int i=0,j=len-2;
   while(i<j)
   {
     //swap(str[i],str[j]);
     char tmp=str[i];
     str[i]=str[j];
     str[j]=tmp;
     i++;
     j--;
   }
}

int main()
{
 
  /*if(argc < 2)
  {
     printf("port No not provided. Program terminated\n");
     exit(1);
  }*/
  
  int sockfd,newsockfd,portno,n;
  char buffer[255];
  struct sockaddr_in serv_addr,cli_addr;
  socklen_t clilen;
  
  sockfd=socket(AF_INET,SOCK_DGRAM,0);
  
  if(sockfd<0)
  {
    printf("error opening socker\n");
    exit(1);
  }
  
  bzero((char *) &serv_addr,sizeof(serv_addr));
  
  portno=9898;
  
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=INADDR_ANY;
  serv_addr.sin_port=htons(portno);
  
  if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
        {
           printf("Bnding Failed\n");
           exit(1);
        }
 clilen=sizeof(serv_addr);
 bzero(buffer,255);
 n=recvfrom(sockfd,buffer,255,0,(struct sockaddr *) &serv_addr,&clilen);
 if(n<0)
 {
   printf("error from recieving\n");
  
  exit(1);
 }
 
 printf("client input is:%s\n",buffer); 
 reverse(buffer);
 printf("output to client:%s",buffer);
 n=sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *) &serv_addr,clilen);
 if(n<0)
 {
   printf("error in sending\n");
   exit(1);
 
 }
 return 0;       
}
