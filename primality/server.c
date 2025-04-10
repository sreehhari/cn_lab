#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
#include<arpa/inet.h>


bool is_prime(int n){
    if(n<2)return false;
    for(int i =2;i*i<=n;i++){
        if(n%i==0)return false;
        return true;
    }
}
int main(){
    char *ip = "127.0.0.1";
    int port =5566;
    
    int sock;
    struct sockaddr_in server_addr,client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024];

    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0){
        perror("error forming the socket\n");
        exit(1);
    }

    printf("socket success\n");

    memset(&server_addr,'\0',sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr));

    while (1)
    {
        bzero(buffer,sizeof(buffer));
        recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr*)&client_addr,&addr_len);
        
        int num = atoi(buffer);
        printf("the number is %d\n",num);
        const char *reply = is_prime(num)?"yes its prims" : "nope not prime";
        sendto(sock,reply,strlen(reply),0,(struct sockaddr*)&client_addr,addr_len);

    }
    close(sock);
    return 0;
    
}
