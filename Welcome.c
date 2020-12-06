#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<arpa/inet.h>
#include <unistd.h>

int main() 
{
    int sock, cli;
    struct sockaddr_in server,client;
    unsigned int len;
    int sent;
    char* message = "Hello, You did it.";
    if((sock = socket(AF_INET, SOCK_STREAM,0))==-1) {
        perror("socket: ");
        exit(-1);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(10000);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, 8);

    len = sizeof(struct sockaddr_in);

    if((bind(sock, (struct sockaddr *)&server, len))==-1) 
    {
        perror("bind");
        exit(-1);
    }

    if(listen(sock,5)==-1) 
    {
        perror("listen");
        exit(-1);
    }

    while(1)
    {
        if((cli=accept(sock, (struct sockaddr *) &client, &len))==-1) {
            perror("accept");
            exit(-1);
        }
        sent = send(cli, message, sizeof(message),0);
        printf("Sent %d bytes to client: %s\n",sent, inet_ntoa(client.sin_addr));
        close(cli);
    }
}