//Author : smsdsl program : Tcp_server fork call usage 
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
	
	int sockfd,retbind,connfd;	
	struct sockaddr_in serv_addr,cli_addr;
	
	//clearing the structure buffer with bzero or memset
	bzero((char *)&serv_addr,sizeof(serv_addr));
	//server port number and client length variable
	int port_number,cli_len;
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
	

		
	retbind=bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if(retbind<0){
		perror("failed to bind the IPV4 adress to the socket!!\n");
		exit(1);
	}
	else{
		printf("server is running at port number : %d\n",port_number);
	}
	int number_of_backlog_connections=5;
	int retlisten=listen(sockfd,number_of_backlog_connections);
	if(retlisten==0){
		printf("listen system call is working perfectly..!\n");
	}
	else{
		printf("lsiten system call failed to keep connections in backlog...!");
	}
	
	cli_len=sizeof(cli_addr);
	connfd=accept(sockfd,(struct sockaddr*)&cli_addr,&cli_len);
	
	if(connfd<0){
		printf("unable to create socket using accept system call\n");
		exit(0);
	}
	else{
		printf("confd socket descriptor is created sucessfully having number is %d\n",connfd);
	}
	pid_t ret;
	ret=fork();
	if(ret==0){
		while(1){
			
				bzero(readbuf,sizeof(readbuf));
				read(connfd,&readbuf,sizeof(readbuf));
				printf("Msg from Cilent : %s\n",readbuf);
			}
	}
	else if(ret>0){		
			while(1){
				
				bzero(writebuf,sizeof(writebuf));
				int buffer_count=0;
				printf("Msg to client :");
				while((writebuf[buffer_count++]=getchar())!='\n');
				write(connfd,&writebuf,sizeof(writebuf));
			}
	}
	else{
		printf("Failed to create child process\n");
	}	
	close(connfd);
	close(sockfd);
	return 0;	
}	


//	compile it using gcc
//	once its sucessful
//	telnet localhost 4500
// 	to close connection from telnet type close
