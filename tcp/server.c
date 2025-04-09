#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){

    char *ip = "127.0.0.1";
    int port = 5566;


    //variables required

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;


    //setting the socket 
    server_sock= socket(AF_INET,SOCK_STREAM,0);
    if(server_sock<0){
        perror("socket initialization failed\n");
        exit(1);
    }
    printf("tcp server socket created \n");


    //clear the server_addr struct 
    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr  = inet_addr(ip);

    //now we bind the server_addr with the server_sock 
    n = bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(n<0){
        perror("error biding\n");
        exit(1);
    }
    printf("bind successful\n");


    //now listen for the conection

    listen(server_sock,5);
    printf("listening for connections\n");
    
    //loop till infinity
    while(1){
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&addr_size);
        printf("client connected\n");


        //to receive a message from the client
        bzero(buffer,sizeof(buffer));
        recv(client_sock,buffer,sizeof(buffer),0);
        
        printf("the received message is %s\n",buffer);

        close(client_sock);
        printf("connection closed\n");



    }





    return 0;
}