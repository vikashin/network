//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux
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
	
#define TRUE 1
#define FALSE 0
#define PORT 8888
	
int main()
{
	int opt = TRUE,nbytes;
	int listener , addrlen , new_socket , client_socket[30] ,
		max_clients = 30 , activity, i ,j, valread , sd;
	int max_sd,newfd;
	struct sockaddr_in address;
		
        char msg[1025]="hung up client at socket: ";
        
        char msg1[100];
	char buffer[1025]; //data buffer of 1K
		
	//set of socket descriptors
	fd_set readfds,master;
		
	//a message
	char *message = "ECHO Daemon v1.0 \r\n";
	
	//initialise all client_socket[] to 0 so not checked
	for (i = 0; i < max_clients; i++)
	{
		client_socket[i] = 0;
	}
		
	//create a master socket
	if( (listener = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	FD_ZERO(&master);
	FD_ZERO(&readfds);
	//set master socket to allow multiple connections ,
	//this is just a good habit, it will work without this
	if( setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
		sizeof(opt)) < 0 )
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	//type of socket created
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
		
	//bind the socket to localhost port 8888
	if (bind(listener, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	printf("Listener on port %d \n", PORT);
		
	//try to specify maximum of 3 pending connections for the master socket
	if (listen(listener, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
		
	//accept the incoming connection
	addrlen = sizeof(address);
	
		
       FD_SET(listener,&master);
       
       max_sd=listener;
	while(TRUE)
	{
		
		readfds=master;

		
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
	
		if ((activity < 0) )
		{
			printf("select error");
			exit(1);
		}
			
		//If something happened on the master socket ,
		//then its an incoming connection
		for(i=0;i<=max_sd;i++){
		if (FD_ISSET(i, &readfds))
		{
		     if(i==listener){
		     
		     
			if ((new_socket = accept(listener,(struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
			{
				perror("accept");
				
			}
			
			else{
			FD_SET(new_socket,&master);
			
			 if( new_socket > max_sd)
			 {
			   max_sd=new_socket;
			 }
			//inform user of socket number - used in send and receive commands
			printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
		         }
		        }
		        else{
			 memset(buffer,0,1025);
			
			nbytes=recv(i, buffer,1025, 0);
			int tmp=strncmp(buffer,"exit",4);
			if(tmp==0)
			{
			  
				char msg[1025]="client left from socket ";
        
                                char msg1[100];
				printf("client left from socket %d\n",i);
				sprintf(msg1,"%d",i);
				strcat(msg,msg1);
				for(int a=0;a<=max_sd;a++)
				{
				  if(FD_ISSET(a,&master)){
				  if(a!=listener && a!=i)
				  if(send(a,msg,sizeof(msg),0)==-1)
			           {
			             perror("send");
			    
			           }
			           }
			        }
			        memset(msg,0,1025);
			        memset(msg1,0,100);
			        close(i);
				FD_CLR(i,&master);
		        }
			else {
			  
			  printf("client at socket %d:%s\n",i,buffer);
			  
			  char cli_msg[1025]="client at socket ";
			  char cli_nu[100];
			  sprintf(cli_nu,"%d:",i);
			  strcat(cli_msg,cli_nu);
			  strcat(cli_msg,buffer);
			  for(j=0;j<=max_sd;j++)
			  {
			    if(FD_ISSET(j,&master)){
			    if( j!=listener && j!=i){
			    if(send(j,cli_msg,1025,0)==-1)
			    {
			      perror("send");
			    
			    }
			    }
			   
			  }
			 }
			}
		     }
		    }
		   }
		  }
 return 0;

			
}

