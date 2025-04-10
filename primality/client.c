#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5566);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("enter the number\n");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\n")]=0;
    sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&server_addr,addr_len);

    bzero(buffer,sizeof(buffer));

    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&server_addr,&addr_len);
    printf("%s\n",buffer);
    close(sockfd);
    return 0;

}