#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    char buffer[1024];
    int n;


    //create the socket 
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0){
        perror("socket creation failed\n");
        exit(1);
    }
    printf("successfully created a socket at port %d",port);

    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //prepare the message

    bzero(buffer,sizeof(buffer));
    char str[100];
    printf("enter the message \n");
    fgets(str,sizeof(str),stdin);
    str[strcspn(str,"/n")]=0;
    strcpy(buffer,str);

    sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&server_addr,sizeof(server_addr));
    close(sock);

    printf("client sent the message successfully\n");

}