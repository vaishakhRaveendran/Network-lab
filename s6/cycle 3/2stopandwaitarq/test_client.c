#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/select.h>

#define timeoutval 5
void main(){
    char* ip="127.0.0.1";
    int port=2345;
    struct sockaddr_in addr;
    char buffer[1024];
    int sockfd;
    socklen_t addr_size;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    memset(&addr,'\0',sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=inet_addr(ip);

    int packet_counter=0;
    while(packet_counter<=3){
        bzero(buffer,1024);
        sprintf(buffer,"%d",packet_counter);
        sendto(sockfd,buffer,1024,0,(struct sockaddr*)&addr,sizeof(addr));
        bzero(buffer,1024);
        addr_size=sizeof(addr);
        struct timeval timeout;
        timeout.tv_sec=timeoutval;
        timeout.tv_usec=0;
        if(socksetopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout))<0){
            perror();
            exit(1)

        }
        else{
             bzero(buffer,1024);
             addr_size=sizeof(addr);
             recvfrom(sockfd,buffer,1024,0,(struct sockaddr*)&addr,&addr_size);
             packet_counter++;

        }

    }




}