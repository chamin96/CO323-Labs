#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* no. of bytes per part */
#define FILE_SIZE 1000

int main(int argc, char**argv) {
    FILE *requestFile;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen;
    char buffer[FILE_SIZE];
    int listenfd, connfd, n, index = 1, i = 0, chr;

    /* one socket is dedicated to listening */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    /* initialize a sockaddr_in struct with our own address information for
    binding the socket */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(32000);

    /* binding */
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof (servaddr));

    /* listen for any incoming connections. */
    listen(listenfd, 0);
    clilen = sizeof (cliaddr);
    printf("Server is running\n");

    /* accept the client with a different socket. */
    connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen); // the uninitialized cliaddr variable is filled in with the
    

    /* getting client request */
    n = recvfrom(connfd, buffer, FILE_SIZE, 0, (struct sockaddr *) &cliaddr, &clilen); // information of the client by recvfrom function
    buffer[n] = 0;
    printf("requested:%s\n", buffer);

    /* open requested file */
    requestFile = fopen(buffer, "r");
    if (requestFile == NULL) {
        char* errorMsg = "error opening file.\n";
        printf("%s", errorMsg);
        sendto(connfd, errorMsg, strlen(errorMsg), 0, (struct sockaddr *) &cliaddr, sizeof (cliaddr));
    }

    /* find file length */
    fseek(requestFile, 0, 2);
    long int size = ftell(requestFile);
    printf("%s size: %ld\n", buffer, size);

    /* calculate no. of serves and send it to client */
    int serves = (size / FILE_SIZE) + 1;
    printf("serves: %d\n", serves);
    sprintf(buffer, "%d\n", serves);
    sendto(connfd, buffer, sizeof (int), 0, (struct sockaddr *) &cliaddr, sizeof (cliaddr));

    rewind(requestFile);

    /* sending file to client */
    while (1) {
        chr = fgetc(requestFile);
        buffer[i++] = chr;
        if (chr == EOF) { // end of file
            buffer[--i] = 0;
            sendto(connfd, buffer, strlen(buffer), 0, (struct sockaddr *) &cliaddr, sizeof (cliaddr));
            break;
        }
        if (ftell(requestFile) == (index * FILE_SIZE)) { // send by part
            sendto(connfd, buffer, strlen(buffer), 0, (struct sockaddr *) &cliaddr, sizeof (cliaddr));
            i = 0;
        }
    }
    fclose(requestFile);

    return 0;
}
