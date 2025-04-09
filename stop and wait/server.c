#include<stdio.h>
#include<stdlib.h>

#define MAX 5

int main(){
    int window_size, frames[MAX], ack, i ,  sent =0;
    printf("enter the window size\n");
    scanf("%d",&window_size);

    printf("enter the %d frames",window_size);
    for(int i=0;i<window_size;i++){
        scanf("%d",&frames[i]);
    }
    while(sent<window_size){
        printf("sending frame %d",frames[sent]);
        printf("waiting for ack\n");
        printf("enter ack for frame %d\n",frames[sent]);
        scanf("%d",&ack);
        if(ack==frames[sent]){
            printf("ack received\n");
            sent++;
        }else{
            printf("ack not received for %d\n",frames[sent]);
        }
    }
    printf("all frames sent succfully\n");
    return 0;
}
