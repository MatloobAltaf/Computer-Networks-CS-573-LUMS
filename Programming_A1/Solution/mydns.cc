
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

int main(int argc, char *argv[])
{
  // define your variables here
	struct hostent* serverInfo; //structre that would store the sturucture returned by gethostbyname()
	struct in_addr internetAdd; //structure to store internet address
	int i = 0;
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
  // Print to standard output

	struct in_addr **ipAddress = (struct in_addr **)serverInfo->h_addr_list;
	while(ipAddress[i] != NULL){
		std::cout<<std::endl;
		std::cout<<"Name : "<< serverInfo->h_name<<std::endl;
		std::cout<<"IP Address : ";
		std::cout<<inet_ntoa(*ipAddress[i]) <<std::endl;
		i++;
	}
 return 0;
}
