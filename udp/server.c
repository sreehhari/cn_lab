#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>


int main(){

    char *ip = "127.0.0.1";
    int port =5566;
    
    int server_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    char buffer[1024];
    int n;

    //INITIALIZE THE SOCKET
    server_sock = socket(AF_INET,SOCK_DGRAM,0);
    if(server_sock<0){
        perror("socket formation failed\n");
        exit(1);
    }

    memset(&server_addr, '\0', sizeof(server_addr));

    //initialize the server_addr 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr=inet_addr(ip);


    //bind the socket to the server_addr
    n= bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(n<0){
        perror("binding failed\n");
        exit(1);
    }
    while (1)
    {
        addr_len=sizeof(client_addr);
        bzero(buffer,sizeof(buffer));

        recvfrom(server_sock,buffer,sizeof(buffer),0,(struct sockaddr*)&client_addr,&addr_len);
        printf("the received message is %s\n",buffer);
 

    }
    close(server_sock);
    




    //reveive from client







    return 0;
}