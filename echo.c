#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<arpa/inet.h>
#include <unistd.h>
#define ERROR -1
#define MAX_CLIENTS 2
#define MAX_DATA 1024

int main(int argc, char** argv)
{
    printf("hello?");
    struct sockaddr_in server, client;
    int sock, cli;
    unsigned int sockaddr_len = sizeof(struct sockaddr_in);
    int data_len;
    char data[MAX_DATA];
    printf("**");
    if((sock=socket(AF_INET, SOCK_STREAM,0))== ERROR)
    {
        perror("Socket: ");
        exit(-1);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(10000);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, 8);

    if((bind(sock, (struct sockaddr *)&server, sockaddr_len))==ERROR) {
        perror("Bind");
        exit(-1);
    }
    if(listen(sock,MAX_CLIENTS)==-1)
    {
        perror("Listen");
        exit(-1);
    }
    printf("*");
    int i=2;
    while(i--)
    {
        printf("Hi");
        if((cli=accept(sock, (struct sockaddr *) &client,&sockaddr_len))==ERROR)
        {
            perror("accept");
            exit(-1);
        }
        printf("New Client connected from port no %d and ip %s", ntohs(client.sin_port), inet_ntoa(client.sin_addr));
        data_len = 1;
        // while(data_len) 
        // {
        //     data_len = recv(cli, data, MAX_DATA,0);
        //     if(data_len)
        //     {
        //         send(cli, data, data_len, 0);
        //         data[data_len]='\0';
        //         printf("Sent Message: %s",data);
        //     }
        // }
        printf("Client Disconnected");
        close(cli);
    }

}