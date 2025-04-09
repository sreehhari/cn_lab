#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    char *ip ="127.0.0.1";
    int port =5566;
    
    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];

    //setting the socket 
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock<0){
        perror("error setting up the socket\n");
        exit(1);
    }
    printf("tcp server setup\n");


    //clear the addr 
    memset(&addr,'\0',sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=port;
    addr.sin_addr.s_addr=inet_addr(ip);


    //now we connect to the server
    connect(sock,(struct sockaddr*)&addr,sizeof(addr));
    printf("connected to the server\n");


    //sending some values
    bzero(buffer,1024);
    char str[100];
    
    printf("enter the message\n");
    fgets(str,sizeof(str),stdin);
    str[strcspn(str, "\n")] = 0; // Removes trailing newline use this to change the blank spaces to something else
    strcpy(buffer,str);
    printf("client sent the message %s\n",buffer);
    //now we send the buffer
    send(sock,buffer,strlen(buffer),0);

    return 0;
}