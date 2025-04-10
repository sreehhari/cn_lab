// ftp_client.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fcntl.h>

int main(){
    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror("Socket error");
        exit(1);
    }
    printf("Client socket created\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Connected to server\n");

    FILE *fp = fopen("file_to_send.txt", "r");
    if(fp == NULL){
        perror("File doesn't exist or can't be opened");
        exit(1);
    }

    // while(fgets(buffer, 1024, fp) != NULL){
    //     send(sock, buffer, strlen(buffer), 0);
    //     bzero(buffer, 1024);
    // }

    while (fgets(buffer,sizeof(buffer),fp)!=NULL)
    {
        send(sock,buffer,strlen(buffer),0);
        bzero(buffer,sizeof(buffer));
    }
    
    printf("File sent successfully\n");
    fclose(fp);
    close(sock);

    return 0;
}
