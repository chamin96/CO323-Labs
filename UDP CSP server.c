/* Sample UDP server */
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[1000];
	char * N;

	char* acknowledge = "ack";

	sockfd = socket(AF_INET,SOCK_DGRAM,0);	//using IPv4 , UDP , one protocol

	servaddr.sin_family = AF_INET;		//address family
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);		//address to be used
	servaddr.sin_port = htons(32000);		//port to be used
	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	while(1){
		len = sizeof(cliaddr);
		n = recvfrom(sockfd, N, 1000, 0, (struct sockaddr *) &cliaddr, &len);
		sendto(sockfd, acknowledge, n, 0, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
		mesg[n] = 0;
		printf("Received: ack\n");

		int N = atoi(N);

		int i = 1;
		while (i<=N){
			len = sizeof(cliaddr);
			n = recvfrom(sockfd, mesg, 1000, 0, (struct sockaddr *) &cliaddr, &len);
			sendto(sockfd, mesg, n, 0, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
			mesg[n] = 0;
			printf("Received: %s\n", mesg);
			i++;
		}
	}


	return 0;
}