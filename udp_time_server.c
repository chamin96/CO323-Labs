#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[1000];

    time_t rawtime;
    struct tm * timeinfo;

	char* banner = "Hello UDP client! Now I'm gonna send time.";
    int size_banner = strlen(banner);

	sockfd = socket(AF_INET,SOCK_DGRAM,0);	//using IPv4 , UDP , one protocol

	servaddr.sin_family = AF_INET;		//address family
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);		//address to be used
	servaddr.sin_port = htons(32000);		//port to be used
	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    len = sizeof(cliaddr);
	n = recvfrom(sockfd, mesg, 1000, 0, (struct sockaddr *) &cliaddr, &len);
	sendto(sockfd, banner, size_banner, 0, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
	mesg[n] = 0;
	printf("Received: %s\n",mesg);
    
	while(1){
	    time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        char* time_str = asctime(timeinfo);
        sendto(sockfd, time_str, strlen(time_str), 0, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
        sleep(1);
	}


	return 0;
}