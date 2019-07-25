/* Sample UDP server */
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[1000];
	char N[6];

	char* acknowledge = "ack";

	sockfd = socket(AF_INET,SOCK_DGRAM,0);	//using IPv4 , UDP , one protocol

	servaddr.sin_family = AF_INET;		//address family
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);		//address to be used
	servaddr.sin_port = htons(32000);		//port to be used
	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	while(1){
		len = sizeof(cliaddr);
		n = recvfrom(sockfd, N, 1000, 0, (struct sockaddr *) &cliaddr, &len);
		sendto(sockfd, "ack", 3, 0, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
		N[n] = 0;

		int dec = 0, len;
		len = strlen(N);
		for(int i=0; i<len; i++){
			dec = dec * 10 + ( N[i] - '0' );
		}
		int N = dec;

		int i = 1;

		while (i<=N){
			len = sizeof(cliaddr);
			n = recvfrom(sockfd, mesg, 1000, 0, (struct sockaddr *) &cliaddr, &len);
			mesg[n] = 0;
			printf("Received: %s\nConverting to UPPERCASE.....\n", mesg);

			int j = 0;
			char str[n];

			while (mesg[j]){
				str[j] = toupper(mesg[j]);
				j++;
			}
			str[j] = 0;
			printf("Done...\nSending to client...\n");

			sendto(sockfd, str, j, 0, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
			i++;
		}
	}


	return 0;
}