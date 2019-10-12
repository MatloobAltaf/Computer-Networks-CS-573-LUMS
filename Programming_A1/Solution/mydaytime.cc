
/*
man7.org/linux/man-pages/man3/gethostname.3.html

*/

#include <stdio.h> // basic I/O
#include <stdlib.h>
#include <sys/types.h> // standard system types
#include <netinet/in.h> // Internet address structures
#include <sys/socket.h> // socket API
#include <arpa/inet.h>
#include <netdb.h> // host to IP resolution
#include <string.h>
#include <unistd.h>
#include <iostream>

#define HOSTNAMELEN 40 // maximal host name length; can make it variable if you want
#define BUFLEN 1024 // maximum response size; can make it variable if you want
#define PORT 13
int main(int argc, char *argv[])
{
  // define your variables here
	struct hostent* serverInfo; //structre that would store the sturucture returned by gethostbyname()
	struct in_addr internetAdd; //structure to store internet address
	int sock;
	int i = 0;
	struct sockaddr_in sockAdd;
	char buffer[BUFLEN];
  // check that there are enough parameters
  if (argc != 2)
    {
      fprintf(stderr, "Usage: mydns <hostname>\n");
      exit(-1);
    }

  // Address resolution stage by using gethostbyname()
	serverInfo = gethostbyname(argv[1]); //returns a pointer to hostnet
 // Write your code here!
	if(serverInfo == NULL){
	std::cout<<"Error: Host Not Found."<<std::endl;
	exit(-1);
	}
	//internetAdd =*(struct in_addr*) serverInfo->h_addr;

	sockAdd.sin_family = AF_INET;
	sockAdd.sin_port = htons(PORT);
	sockAdd.sin_addr = *(struct in_addr*) (serverInfo->h_addr);


	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock==-1){
		std::cout<<"Error: Failed to mad Socket"<<std::endl;
		exit(-1);
}
	if(connect(sock,(struct sockaddr*)&sockAdd,sizeof(sockAdd))==-1){
	std::cout<<"Error: Failed to Connect"<<std::endl;
	exit(-1);
}
	bzero(buffer,BUFLEN);
	if(write(sock,"Send Help!",strlen("Send Help!"))==-1){
	std::cout<<"Error: Faild to send Message "<<std::endl;
	exit(-1);
}

if(read(sock,buffer,BUFLEN)==-1){
	std::cout<<"Error: Failed to recieve Responce"<<std::endl;
	exit(-1);
}
  // Print to standard output
	std::cout<<"time: "<<buffer<<std::endl;
 return 0;
}
