/* Sample UDP server */
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>

int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[1000];

	char* banner = "Hello UDP client! This is UDP server";

	sockfd = socket(AF_INET,SOCK_DGRAM,0);	//using IPv4 , UDP , one protocol

	servaddr.sin_family = AF_INET;		//address family
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);		//address to be used
	servaddr.sin_port = htons(32000);		//port to be used
	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	while(1){
		len = sizeof(cliaddr);
		n = recvfrom(sockfd, mesg, 1000, 0, (struct sockaddr *) &cliaddr, &len);
		sendto(sockfd, banner, n, 0, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
		mesg[n] = 0;
		printf("Received: %s\n",mesg);
	}


	return 0;
}