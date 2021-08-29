//Author : smsdsl
//program : Tcp_client [ send message to server]	//fork server 
#include<stdio.h>
#include<sys/types.h>	
#include<sys/socket.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<strings.h>
#include<arpa/inet.h>
#include<unistd.h>

void error(char *msg){
	perror(msg);
	exit(1);
}	

int main(int argc,char * argv[]){

	//checking command line argument
	if(argc<2){
		printf("provide the port number...!\n");
		printf("use this format : ./filename <port-number>\n");
		exit(1);
	}	
	
	int sockfd;	
	struct sockaddr_in serv_addr;
	
	//clearing the structure buffer with bzero or memset
	bzero((char *)&serv_addr,sizeof(serv_addr));
	//server port number and client length variable
	int port_number;
	//buffer to be used for reading and writing
	char readbuf[1024],writebuf[1024];
	
	port_number=atoi(argv[1]);//typecast to a integer format
	
	//Initialize the structure members
	serv_addr.sin_family=AF_INET;	//adress family -->IPV4
	serv_addr.sin_port=htons(port_number);//port number
	serv_addr.sin_addr.s_addr=INADDR_ANY;	//can be any IP addr
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);	//TCP-SOCK_STREAM
	if(sockfd<0){
		perror("socket creation failed !!\n");
		exit(1);
	}
	else{
		printf("Master sockeet connection sucessful\n");
	}
	//connect system call
	int retconnect=connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(retconnect==0){
		printf("Bind/connect sucessful with server\n");
	}
	else{
		printf("Connection failed with TCP server \n");
	}
	pid_t ret;
	ret=fork();
	if(ret == 0)
    {
            while(1)
            {
                    bzero(readbuf,sizeof(readbuf));
                    read(sockfd,&readbuf, sizeof(readbuf));
                    printf("Msg from Server : %s\n",readbuf);

            }
            
    }

    else if(ret > 0)
    {
        while(1)
        {
                    bzero(writebuf,sizeof(writebuf));
                    int buffer_count = 0;
                    printf("Msg to Server : ");
                    while((writebuf[buffer_count++] = getchar()) != '\n');
                    write(sockfd,&writebuf, sizeof(writebuf));
        }
    }

    else
    {
        perror("Failed to Create Child Process !! Fork () system call failed !!\n");
    }

	
	close(sockfd);
	return 0;	
}	


//	compile it using gcc
//	once its sucessful
//	telnet localhost 4500
// 	to close connection from telnet type close
