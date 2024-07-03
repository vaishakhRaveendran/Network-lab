#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

void main(){
    char* ip="127.0.0.1";
    int port=2345;
    struct sockaddr_in client_addr;
    char buffer[1024];
    int client_sock,connection_status;


    client_sock=socket(AF_INET,SOCK_STREAM,0);
    if(client_sock<0){
        printf("[+] TCP server socket error.\n");
    }
    
    //DEFINITION OF CLIENT.......................
    memset(&client_addr,'\0',sizeof(client_addr));
    client_addr.sin_family=AF_INET;
    client_addr.sin_port=port;
    client_addr.sin_addr.s_addr=inet_addr(ip);

    //ESTABLISH CONNECTION.......................
    connection_status=connect(client_sock,(struct addr*)&client_addr,sizeof(client_addr));
    if(connection_status<0){
        printf("[+] CANT ESTABLISH CONNECTION[+]\n");
    }
    bzero(buffer,1024);
    strcpy(buffer,"Hello monchaa");
    send(client_sock,buffer,strelen(buffer),0);
    close(client_sock);
    printf(" Disconnected from the server .\n");



}