/* Sample UDP client */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr;
	char sendline[] = "Hello UDP server! This is UDP client";
	char recvline[1000];
	char * N;

	if (argc != 3)
	{
		printf("usage: ./%s <IP address> <Number of Sentences>\n",argv[0]);
		return -1;
	}

	N = argv[2];

	sockfd = socket(AF_INET,SOCK_DGRAM,0);	//IPv4, UDP, one protocol

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(32000);

	sendto(sockfd, N, strlen(N), 0, (struct sockaddr*) &servaddr, sizeof(servaddr));
	n = recvfrom(sockfd, recvline, 10000, 0, NULL, NULL);
	recvline[n] = 0;
	printf("Received: %s\n",recvline);

	N = atoi(argv[2]);

	int i = 1;
	while(i<=N){
		char str[1000];
		printf("Enter Sentence %d : ", i);
		scanf("%s", str);

		sendto(sockfd, str, strlen(sendline), 0, (struct sockaddr*) &servaddr, sizeof(servaddr));
		n = recvfrom(sockfd, recvline, 10000, 0, NULL, NULL);
		recvline[n] = 0;
		printf("Received: %s\n",recvline);

		i++;
	}


	return 0;
}