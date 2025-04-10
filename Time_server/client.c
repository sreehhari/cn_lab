#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    char *ip ="127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buffer[1024];
    
    sock = socket(AF_INET,SOCK_DGRAM,0);

    memset(&server_addr,'\0',sizeof(server_addr));

    server_addr.sin_family=AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);


    sendto(sock,buffer,1,0,(struct sockaddr*)&server_addr,addr_len);
    bzero(buffer,sizeof(buffer));
    recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr*)&server_addr,&addr_len);
    printf("the time is : %s",buffer);
    close(sock);
    return 0;
}