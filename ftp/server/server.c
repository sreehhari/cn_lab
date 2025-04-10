#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fcntl.h>


int main(){
    char *ip = "127.0.0.1";
    int port = 5566;

    int server_sock,clinet_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    int n;
    char buffer[1024];

    server_sock = socket(AF_INET,SOCK_STREAM,0);
    if(server_sock<0){
        perror("error making the socket\n");
        exit(1);
    }
    printf("successfully created the socket\n");

    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    n = bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(n<0){
        perror("erro binding \n");
        exit(1);
    }
    printf("bind success\n");

    listen(server_sock,5);
    printf("listening\n");
    addr_len = sizeof(client_addr);
    clinet_sock = accept(server_sock,(struct sockaddr*)&client_addr,addr_len);
    printf("client connected\n");

    FILE *fp = fopen("test.txt","w");
    if(fp==NULL){
        perror("file not found\n");
        exit(1);
    }
    while(1){
        bzero(buffer,sizeof(buffer));
        int bytes_received = recv(clinet_sock,buffer,sizeof(buffer),0);
        if(bytes_received<=0){
            break;
        }
        fprintf(fp,"%s",buffer);

        printf("file received successfully\n");
        fclose(fp);
        close(clinet_sock);
        close(server_sock);

        return 0;
    }
}