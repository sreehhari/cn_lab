#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>


int main(){

    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024];
    int n;

    //initialize the socket 
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0){
        perror("error creating the socket\n");
        exit(1);
    }
    printf("successfully created the socket\n");

    //setup the server_addr
    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //now we bind the sock with the server_addr

    n = bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(n<0){
        perror("bind failed\n");
        exit(0);
    }
    printf("bind successful\n");

 //receive the first ping from the client

 recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr*)&client_addr,&addr_len);
 printf("client pingged\n");
  bzero(buffer,sizeof(buffer));
 time_t now = time(NULL);
 snprintf(buffer,sizeof(buffer),"current time : %s",ctime(&now));

 sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,addr_len);
 close(sock);

 return 0;



}