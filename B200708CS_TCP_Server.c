#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<unistd.h>  //read and write
#include<sys/types.h>  // for size_t and ssize_t
#include<netinet/in.h>  //define struct sockadder_in
#include<arpa/inet.h>
#include<netdb.h>

void reverse(char *str)
{
  int len=strlen(str);
  
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
   struct sockaddr_in server;
   int sock=socket(AF_INET,SOCK_STREAM,0);
   
   if(sock<0)
   {
     printf("error in socket creation");
     exit(1);
   }
   
   int portno=8888;
   server.sin_family=AF_INET;
   server.sin_port=htons(portno);
   
   //server.sin_addr.s_addr=INADDR_ANY;
   
   int t2=inet_pton(AF_INET,"127.0.0.1",&(server.sin_addr));
  
   int t1=bind(sock,(struct sockaddr *) &server,sizeof(server));
   
      if(t1<0)
      {
        printf("error in binding");
        exit(1);
      }
      
   
   
   listen(sock,10);
   
   
   struct sockaddr_in client;
   socklen_t clienlen=sizeof(client);
   int newsock=accept(sock,(struct sockaddr *) &client,&clienlen);
   if(newsock<0)
   {
     printf("error in accepting");
     exit(1);
   }
   
   char buffer[255];
   memset(buffer,0,sizeof(buffer));
   int recvbyte=recv(newsock,buffer,255,0);
   
  
   if(recvbyte<0)
   {
     printf("error in recieving");
     exit(1);
   }
   
   /*int tmp=recvbyte/sizeof(char);
   printf("%d\n",tmp);*/
   
   printf("client:%s",buffer);
  
   reverse(buffer);
   int sendbyte=send(newsock,buffer,strlen(buffer),0);
   if(sendbyte<0)
   {
     printf("error in sending");
     exit(1);
   }
   printf("server:%s",buffer);
   close(newsock);
   close(sock);
   return 0;
}
     
